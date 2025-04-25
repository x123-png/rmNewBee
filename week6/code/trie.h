//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// trie.h
//
// Identification: src/include/primer/trie.h
//
// Copyright (c) 2015-2025, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <algorithm>
#include <cstddef>
#include <future>  // NOLINT
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string_view>
#include <string>

namespace bustub {

/// A special type that will block the move constructor and move assignment operator. Used in TrieStore tests.
class MoveBlocked {
 public:
  explicit MoveBlocked(std::future<int> wait) : wait_(std::move(wait)) {}

  MoveBlocked(const MoveBlocked &) = delete;
  MoveBlocked(MoveBlocked &&that) noexcept {
    if (!that.waited_) {
      that.wait_.get();
    }
    that.waited_ = waited_ = true;
  }

  auto operator=(const MoveBlocked &) -> MoveBlocked & = delete;
  auto operator=(MoveBlocked &&that) noexcept -> MoveBlocked & {
    if (!that.waited_) {
      that.wait_.get();
    }
    that.waited_ = waited_ = true;
    return *this;
  }

  bool waited_{false};
  std::future<int> wait_;
};

// A TrieNode is a node in a Trie.
class TrieNode {
 public:
  // Create a TrieNode with no children.
  TrieNode() = default;

  // Create a TrieNode with some children.
  explicit TrieNode(std::map<char, std::shared_ptr<const TrieNode>> children) : children_(std::move(children)) {}

  virtual ~TrieNode() = default;

  // Clone returns a copy of this TrieNode. If the TrieNode has a value, the value is copied. The return
  // type of this function is a unique_ptr to a TrieNode.
  //
  // You cannot use the copy constructor to clone the node because it doesn't know whether a `TrieNode`
  // contains a value or not.
  //
  // Note: if you want to convert `unique_ptr` into `shared_ptr`, you can use `std::shared_ptr<T>(std::move(ptr))`.
  virtual auto Clone() const -> std::unique_ptr<TrieNode> { return std::make_unique<TrieNode>(children_); }

  // A map of children, where the key is the next character in the key, and the value is the next TrieNode.
  // You MUST store the children information in this structure. You are NOT allowed to remove the `const` from
  // the structure.
  std::map<char, std::shared_ptr<const TrieNode>> children_;

  // Indicates if the node is the terminal node.
  bool is_value_node_{false};

  // You can add additional fields and methods here except storing children. But in general, you don't need to add extra
  // fields to complete this project.
};

// A TrieNodeWithValue is a TrieNode that also has a value of type T associated with it.
template <class T>
class TrieNodeWithValue : public TrieNode {
 public:
  // Create a trie node with no children and a value.
  explicit TrieNodeWithValue(std::shared_ptr<T> value) : value_(std::move(value)) { this->is_value_node_ = true; }

  // Create a trie node with children and a value.
  TrieNodeWithValue(std::map<char, std::shared_ptr<const TrieNode>> children, std::shared_ptr<T> value)
      : TrieNode(std::move(children)), value_(std::move(value)) {
    this->is_value_node_ = true;
  }

  // Override the Clone method to also clone the value.
  //
  // Note: if you want to convert `unique_ptr` into `shared_ptr`, you can use `std::shared_ptr<T>(std::move(ptr))`.
  auto Clone() const -> std::unique_ptr<TrieNode> override {
    return std::make_unique<TrieNodeWithValue<T>>(children_, value_);
  }

  // The value associated with this trie node.
  std::shared_ptr<T> value_;
};

// A Trie is a data structure that maps strings to values of type T. All operations on a Trie should not
// modify the trie itself. It should reuse the existing nodes as much as possible, and create new nodes to
// represent the new trie.
//
// You are NOT allowed to remove any `const` in this project, or use `mutable` to bypass the const checks.
class Trie {
 private:
  // The root of the trie.
  std::shared_ptr<const TrieNode> root_{nullptr};

  // Create a new trie with the given root.
  explicit Trie(std::shared_ptr<const TrieNode> root) : root_(std::move(root)) {}

 public:
  // Create an empty trie.
  Trie() = default;

  template <class T>
  auto Get(std::string_view key) const -> const T *{
    auto node = this->root_;

    if(node == nullptr)
        return nullptr;

    size_t idx = 0;

    while (idx < key.size()) {
      if (node->children_.find(key[idx]) == node->children_.end())
        return nullptr;
      node = node->children_.at(key[idx]);
      idx++;
    }

    auto res=dynamic_cast<const TrieNodeWithValue<T>*>(node.get());
    if(res != nullptr)
        return res->value_.get();
    return nullptr;
  }

  template<typename T>
  std::shared_ptr<const TrieNode> _insert(std::string_view key, std::shared_ptr<const TrieNode> oriNode,int idx,T value) const
  {
      if (idx == key.size()) {
          if(oriNode == nullptr)
              return std::make_shared<TrieNodeWithValue<T>>(std::make_shared<T>(value));
          else
              return std::make_shared<TrieNodeWithValue<T>>(oriNode->children_,std::make_shared<T>(value));
      }

    char ch = key[idx];

    std::map<char, std::shared_ptr<const TrieNode>> children;

    if (oriNode != nullptr)
    {
      children = oriNode->children_;
      if (oriNode->children_.find(ch) == oriNode->children_.end())
          children[ch] = _insert(key, nullptr, idx + 1, value);
      else children[ch] = _insert(key, oriNode->children_.at(ch), idx + 1, value);
    }
    else
    {
        children[ch] = _insert(key, nullptr, idx + 1, value);
    }

    auto res = oriNode == nullptr ? std::make_shared<TrieNode>() : oriNode->Clone();
    res->children_ = children;
    return res;
  }

  template <class T>
  auto Put(std::string_view key, T value) const -> Trie
  {
    Trie trie;
    trie.root_= _insert(key, root_, 0, value);
    return trie;
  }

  std::shared_ptr<const TrieNode> _remove(std::string_view key, std::shared_ptr<const TrieNode> oriNode,int idx) const
  {
      if (idx == key.size()) {
          if (oriNode == nullptr)
              return nullptr;
          else if (oriNode->children_.size() == 0 && !oriNode->is_value_node_)
              return nullptr;
          else
              return std::make_shared<TrieNode>(oriNode->children_);
      }

    char ch = key[idx];

    std::map<char, std::shared_ptr<const TrieNode>> children;

    if (oriNode->children_.find(ch) == oriNode->children_.end())
        children = oriNode->children_;
    else
    {
      children = oriNode->children_;

      auto res = _remove(key,  oriNode->children_.at(ch), idx + 1);
      if (!res->is_value_node_ && res->children_.size() == 0) {
          children.erase(ch);
      }
      else children[ch] = res;
    }

    auto res = oriNode->Clone();
    res->children_ = children;

    return res;
  }

  auto Remove(std::string_view key) const -> Trie
  {
    Trie trie;
    trie.root_= _remove(key, root_, 0);
    if(trie.root_->children_.size() == 0)
        trie.root_ = nullptr;
    return trie;
  }

  // Get the root of the trie, should only be used in test cases.
  auto GetRoot() const -> std::shared_ptr<const TrieNode> { return root_; }
};

}  // namespace bustub
