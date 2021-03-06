#ifndef OAK_LINKED_HASHMAP_H
#define OAK_LINKED_HASHMAP_H

#include <list>
#include <unordered_map>

namespace oak
{
template<typename K, typename V>
class LinkedHashMap {
    public:
        struct ListNode {
            K key;
            V data;
        };

        struct Iterator {
            typedef ListNode* Pointer;
            typedef ListNode& Reference;

            Iterator(typename std::list<ListNode>::iterator iter)
                : mListIter(iter)
            {
            }

            Reference operator*() const noexcept
            {
                return *mListIter;
            }

            Pointer operator->() const noexcept
            {
                return &(this->operator*());
            }

            Iterator& operator++() noexcept
            {
                ++mListIter;
                return *this;
            }

            Iterator operator++(int) noexcept
            {
                Iterator temp = *this;
                ++mListIter;
                return temp;
            }

            Iterator& operator--() noexcept
            {
                --mListIter;
                return *this;
            }

            Iterator& operator--(int) noexcept
            {
                Iterator temp = *this;
                --mListIter;
                return temp;
            }

            bool operator==(const Iterator& rhs) const noexcept
            {
                return mListIter == rhs.mListIter;
            }

            bool operator!=(const Iterator& rhs) const noexcept
            {
                return !this->operator==(rhs);
            }

            typename std::list<ListNode>::iterator mListIter;
        };

        struct ConstIterator {
            typedef const ListNode* Pointer;
            typedef const ListNode& Reference;

            ConstIterator(typename std::list<ListNode>::const_iterator iter)
                : mListIter(iter)
            {
            }

            ConstIterator(const Iterator& iter)
                : mListIter(iter.mListIter)
            {
            }

            Reference operator*() const noexcept
            {
                return *mListIter;
            }

            Pointer operator->() const noexcept
            {
                return &(this->operator*());
            }

            ConstIterator& operator++() noexcept
            {
                ++mListIter;
                return *this;
            }

            ConstIterator operator++(int) noexcept
            {
                Iterator temp = *this;
                ++mListIter;
                return temp;
            }

            ConstIterator& operator--() noexcept
            {
                --mListIter;
                return *this;
            }

            ConstIterator& operator--(int) noexcept
            {
                Iterator temp = *this;
                --mListIter;
                return temp;
            }

            bool operator==(const ConstIterator& rhs) const noexcept
            {
                return mListIter == rhs.mListIter;
            }

            bool operator!=(const ConstIterator& rhs) const noexcept
            {
                return !this->operator==(rhs);
            }

            typename std::list<ListNode>::const_iterator mListIter;
        };
    public:
        LinkedHashMap()
        {
        }

        ~LinkedHashMap()
        {
        }

        void add(const K& key, const V& val)
        {
            auto it = mMap.find(key);
            if (it != mMap.end()) {
                it->second->data = val; 
            } else {
                mList.push_back(ListNode{key, val});
                mMap[key] = --mList.end();
            }
        }

        void remove(const K& key)
        {
            auto it = mMap.find(key);
            if (it == mMap.end()) {
                return;
            }
            mList.erase(it->second);
            mMap.erase(it);
        }

        Iterator erase(ConstIterator position)
        {
            auto listIter = position.mListIter;
            const K& key = listIter->key;
            auto mapIt = mMap.find(key);
            if (mapIt != mMap.end()) {
                mMap.erase(mapIt);
            }

            auto next = mList.erase(listIter);
            return Iterator{next};
        }

        void popFront()
        {
            if (!empty()) {
                erase(this->begin());
            }
        }

        bool find(const K& key, V* pVal) const
        {
            auto it = mMap.find(key);
            if (it == mMap.end()) {
                return false;
            }

            if (pVal != nullptr) {
                *pVal = it->second->data;
            }
            return true;
        }

        int size() const 
        {
            return mList.size();
        }

        bool empty() const 
        {
            return mList.empty();
        }

        Iterator begin() 
        {
            return Iterator(mList.begin());
        }

        Iterator end() 
        {
            return Iterator(mList.end());
        }

        ConstIterator begin() const
        {
            return ConstIterator(mList.begin());
        }

        ConstIterator end() const
        {
            return ConstIterator(mList.end());
        }
    private:

        std::list<ListNode> mList;
        typedef std::unordered_map<K, typename std::list<ListNode>::iterator> KvMap;
        KvMap mMap;
};
}


#endif // OAK_LINKED_HASHMAP_H
