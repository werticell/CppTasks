#include <utility>
#include <iostream>

template<typename T>
class List {
private:

    struct NodeBase;
    struct Node;

    template<bool IsConst, typename ListType>
    class ListIterator;

    struct NodeBase {
        NodeBase(NodeBase* left, NodeBase* right) : next(right), prev(left) {}

        NodeBase* prev;
        NodeBase* next;
    };

    struct Node : public NodeBase {
        Node(NodeBase* left, NodeBase* right, const T& data) : NodeBase(left, right), data(data) {}

        template<typename... Args>
        Node(NodeBase* left, NodeBase* right, Args&&... args) : NodeBase(left, right), data(std::forward<Args...>(args...)) {}
        T data;
    };

    NodeBase* head;
    NodeBase* tail;
    size_t list_size;

public:
    using value_type = T;
    using iterator = ListIterator<false, List<T>>;
    using const_iterator = ListIterator<true, const List<T>>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    List();
    explicit List(size_t count, const T& value = T());
    ~List();

    List(const List<T>& other);
    List(List<T>&& other) noexcept;

    List& operator=(const List<T>& other);
    List& operator=(List<T>&& other) noexcept;


    size_t size() const;
    bool empty() const;
    void clear();


    T& front();
    const T& front() const;
    T& back();
    const T& back() const;


    iterator begin() { return iterator(this, head->next); }
    const_iterator begin() const { return const_iterator(this, head->next); }

    iterator end() { return iterator(this, tail); }
    const_iterator end() const { return const_iterator(this, tail); }

    reverse_iterator rbegin() { return reverse_iterator(this, tail->prev); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(this, tail->prev); }

    reverse_iterator rend() { return reverse_iterator(this, head); }
    const_reverse_iterator rend() const { return const_reverse_iterator(this, head); }

    const_iterator cbegin() const { return const_iterator(this, head->next); }
    const_iterator cend() const { return const_iterator(this, tail); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(this, tail->prev); }
    const_reverse_iterator crend() const { return const_reverse_iterator(this, head); }

    template<typename... Args>
    void emplace_back(Args&&... args);
    template<typename... Args>
    void emplace_front(Args&&... args);

    void push_back(const T& value);
    void push_back(T&& value);
    void push_front(const T& value);
    void push_front(T&& value);

    void pop_back();
    void pop_front();


    template<bool IsConst, typename ListType, typename... Args>
    iterator emplace(ListIterator<IsConst, ListType> pos, Args&&... args);
    template<bool IsConst, typename ListType>
    iterator insert(ListIterator<IsConst, ListType> pos, const T& value);
    template<bool IsConst, typename ListType>
    iterator insert(ListIterator<IsConst, ListType> pos, T&& value);
    template<bool IsConst, typename ListType, typename InputIterator>
    iterator insert(ListIterator<IsConst, ListType> pos,
                    InputIterator first, InputIterator last);

    template<bool IsConst, typename ListType>
    iterator erase(ListIterator<IsConst, ListType> pos);
    template<bool IsConst, typename ListType>
    iterator erase(ListIterator<IsConst, ListType> first, ListIterator<IsConst, ListType> last);


    void reverse();
    void unique();


    void print() const;

};

template<typename T>
void List<T>::print() const {
    if(list_size == 0)
        return;
    Node* current = static_cast<Node*>(head->next);
    for(size_t i = 0; i < list_size - 1; ++i) {
        std::cout << current->data << " ";
        current = static_cast<Node*>(current->next);
    }
    std::cout << current->data << " ";
}

template<typename T>
List<T>::List() : list_size(0), head(new NodeBase(nullptr, nullptr)), tail(new NodeBase(nullptr, nullptr)) {
    head->next = tail;
    tail->prev = head;
}

template<typename T>
List<T>::List(size_t count, const T& value) : List() {
    list_size = count;
    if(count == 0)
        return;

    Node* current_node = new Node(head, nullptr, value);
    head->next = current_node;

    for(size_t i = 1; i < count; ++i) {
        Node* new_node = new Node(current_node, nullptr, value);
        current_node->next = new_node;
        current_node = new_node;
    }
    current_node->next = tail;
    tail->prev = current_node;

}

template<typename T>
List<T>::List(const List<T>& other) : List() {
    if(other.list_size == 0)
        return;
    list_size = other.list_size;

    Node* current_other_node = static_cast<Node*>(other.head->next);
    Node* current_node = new Node(head, nullptr, current_other_node->data);
    head->next = current_node;

    for(size_t i = 1; i < other.list_size; ++i) {
        current_other_node = static_cast<Node*>(current_other_node->next);

        Node* new_node = new Node(current_node, nullptr, current_other_node->data);
        current_node->next = new_node;
        current_node = new_node;
    }
    current_node->next = tail;
    tail->prev = current_node;
}

template<typename T>
List<T>::List(List<T>&& other) noexcept : List() {
    if(other.list_size == 0)
        return;
    std::swap(list_size, other.list_size);
    std::swap(head, other.head);
    std::swap(tail, other.tail);

}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    if(this == &other)
        return *this;
    List<T> copy(other);
    *this = std::move(copy);
    return *this;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& other) noexcept {
    if(this == &other)
        return *this;
    std::swap(list_size, other.list_size);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    return *this;
}

template<typename T>
List<T>::~List() {
    clear();
    delete head;
    delete tail;

}

template<typename T>
size_t List<T>::size() const {
    return list_size;
}

template<typename T>
bool List<T>::empty() const {
    return list_size == 0;
}

template<typename T>
void List<T>::clear() {
    if(list_size == 0)
        return;
    Node* current_node = static_cast<Node*>(head->next);
    for(size_t i = 0; i < list_size - 1; ++i) {
        current_node = static_cast<Node*>(current_node->next);
        delete current_node->prev;
    }

    delete tail->prev;
    head->next = tail;
    tail->prev = head;
    list_size = 0;
}

template<typename T>
T& List<T>::front() {
    return static_cast<Node*>(head->next)->data;
}

template<typename T>
T& List<T>::back() {
    return static_cast<Node*>(tail->prev)->data;
}

template<typename T>
const T& List<T>::front() const {
    return static_cast<Node*>(head->next)->data;
}

template<typename T>
const T& List<T>::back() const {
    return static_cast<Node*>(tail->prev)->data;
}

template<typename T>
template<typename... Args>
void List<T>::emplace_back(Args&&... args) {
    Node* new_node = new Node(tail->prev, tail, std::forward<Args...>(args...));
    new_node->prev->next = new_node;
    new_node->next->prev = new_node;
    ++list_size;
}

template<typename T>
template<typename... Args>
void List<T>::emplace_front(Args&&... args) {
    Node* new_node = new Node(head, head->next, std::forward<Args...>(args...));
    new_node->prev->next = new_node;
    new_node->next->prev = new_node;
    ++list_size;
}

template<typename T>
void List<T>::push_back(const T& value) {
    emplace_back(value);

}

template<typename T>
void List<T>::push_back(T&& value) {
    emplace_back(std::move(value));
}

template<typename T>
void List<T>::push_front(const T& value) {
    emplace_front(value);
}

template<typename T>
void List<T>::push_front(T&& value) {
    emplace_front(std::move(value));
}

template<typename T>
void List<T>::pop_front() {
    if(list_size == 0)
        return;

    Node* deleted_node = static_cast<Node*>(head->next);
    head->next = deleted_node->next;
    deleted_node->next->prev = head;
    delete deleted_node;
    --list_size;
}

template<typename T>
void List<T>::pop_back() {
    if(list_size == 0)
        return;

    Node* deleted_node = static_cast<Node*>(tail->prev);
    tail->prev = deleted_node->prev;
    deleted_node->prev->next = tail;
    delete deleted_node;
    --list_size;
}

template<typename T>
void List<T>::reverse() {
    NodeBase* cur = tail->prev;
    std::swap(cur->prev, cur->next);
    cur->prev = head;
    head->next = cur;

    for(size_t i = 1; i < list_size; ++i) {
        cur = cur->next;
        std::swap(cur->prev, cur->next);
    }

    cur->next = tail;
    tail->prev = cur;
}

template<typename T>
template<bool IsConst, typename ListType, typename... Args>
typename List<T>::iterator List<T>::emplace(List<T>::ListIterator<IsConst, ListType> pos, Args&&... args) {
    if(pos == iterator(this, head))
        ++pos;
    Node* new_node = new Node(pos.ptr->prev, pos.ptr, std::forward<Args...>(args...));
    NodeBase* prev = pos.ptr->prev;
    prev->next = new_node;
    pos.ptr->prev = new_node;
    ++list_size;
    return iterator(this, new_node);
}

template<typename T>
template<bool IsConst, typename ListType>
typename List<T>::iterator List<T>::insert(ListIterator<IsConst, ListType> pos, T&& value) {
    return emplace(pos, std::move(value));
}

template<typename T>
template<bool IsConst, typename ListType>
typename List<T>::iterator List<T>::insert(ListIterator<IsConst, ListType> pos, const T& value) {
    return emplace(pos, value);
}

template<typename T>
template<bool IsConst, typename ListType, typename InputIterator>
typename List<T>::iterator List<T>::insert(ListIterator<IsConst, ListType> pos,
                                            InputIterator first, InputIterator last) {
    NodeBase* it_prev = pos.ptr->prev;
    while(first != last) {
        insert(pos, *first);
        ++first;
    }
    return iterator(this, it_prev->next);
}

template<typename T>
template<bool IsConst, typename ListType>
typename List<T>::iterator List<T>::erase(ListIterator<IsConst, ListType> pos) {
    NodeBase* prev_pos = pos.ptr->prev;
    NodeBase* next_pos = pos.ptr->next;
    prev_pos->next = next_pos;
    next_pos->prev = prev_pos;
    --list_size;
    delete pos.ptr;
    return iterator(this, next_pos);
}

template<typename T>
template<bool IsConst, typename ListType>
typename List<T>::iterator List<T>::erase(ListIterator<IsConst, ListType> first,
                                          ListIterator<IsConst, ListType> last) {
    while(first != last) {
        first = erase(first);
    }
    return last;
}

template<typename T>
void List<T>::unique() {
    if(list_size == 0 || list_size == 1)
        return;
    for (iterator cur = begin(), cur_next = ++begin(); cur_next != end();) {
        if (*cur == *cur_next)
            cur_next = erase(cur_next);
        else
            cur = cur_next++;

    }
}




template<typename T>
template<bool IsConst, typename ListType>
class List<T>::ListIterator {
private:
    ListType* list;
    NodeBase* ptr;
public:
    friend class List<T>;
    using value_type = T;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using pointer = std::conditional_t<IsConst, const T*, T*>;
    using reference = std::conditional_t<IsConst, const T&, T&>;

    ListIterator(ListType* list, NodeBase* ptr) : list(list), ptr(ptr) {}
    ListIterator(const ListIterator<IsConst, ListType>& other) : list(other.list), ptr(other.ptr) {}

    reference operator*() { return static_cast<Node*>(ptr)->data; }
    reference operator*() const { return static_cast<Node*>(ptr)->data; }
    pointer operator->() { return &(static_cast<Node*>(ptr)->data); }
    pointer operator->() const { return &(static_cast<Node*>(ptr)->data); }

    // стандартный list итератор тоже зациклен
    ListIterator<IsConst, ListType>& operator++() {
        if(ptr == list->tail)
            ptr = list->head->next;
        else
            ptr = ptr->next;
        return *this;
    }

    ListIterator<IsConst, ListType> operator++(int) {
        ListIterator<IsConst, ListType> copy(*this);
        ++(*this);
        return copy;
    }

    ListIterator<IsConst, ListType>& operator--() {
        if(ptr == list->head)
            ptr = list->tail->prev;
        else
            ptr = ptr->prev;
        return *this;
    }

    ListIterator<IsConst, ListType> operator--(int) {
        ListIterator<IsConst, ListType> copy(*this);
        --(*this);
        return copy;
    }

    template<bool IsConstOther, typename OtherListType>
    bool operator==(const ListIterator<IsConstOther, OtherListType>& other) const {
        return ptr == other.ptr && list == other.list;
    }

    template<bool IsConstOther, typename OtherListType>
    bool operator!=(const ListIterator<IsConstOther, OtherListType>& other) const {
        return !(*this == other);
    }

};


