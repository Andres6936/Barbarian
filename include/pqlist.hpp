/*
* Barbarian!
* Copyright (C) Zach Wilder 2018
* 
* This file is a part of Barbarian!
*
* Barbarian! is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Barbarian! is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Barbarian!.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef PQLIST_HPP
#define PQLIST_HPP

namespace wsl
{

template<typename T>
class PQNode
{
    public:
        PQNode(T a, float p) : data(a), priority(p) { next = NULL; }

        T data;
        float priority;
        PQNode<T> * next;
};

template<typename T>
class PQList
{
    public:
        PQList();
        PQList(T data, float priority);
        ~PQList();
        
        PQNode<T> * head() { return head_; }
        PQNode<T> * tail() { return tail_; }

        void push(T data, float priority);
        T pop();
        T peek();

        bool isEmpty() { return head_ == NULL; }
    private:
        PQNode<T> * head_;
        PQNode<T> * tail_;
};

template<typename T>
PQList<T>::PQList()
{
    head_ = NULL;
    tail_ = NULL;
}

template<typename T>
PQList<T>::PQList(T data, float priority)
{
    head_ = NULL;
    tail_ = NULL;
    push(data, priority);
}

template<typename T>
PQList<T>::~PQList()
{
    PQNode<T> * current = head_;
    PQNode<T> * next;

    while(current != NULL)
    {
        next = current->next;
        delete(current);
        current = next;
    }
}

template<typename T>
void PQList<T>::push(T data, float priority)
{
    PQNode<T> * newNode = new PQNode<T>(data, priority);
    if(head_ == NULL)
    {
        head_ = newNode;
    }
    else if(head_->priority > newNode->priority)
    {
        newNode->next = head_;
        head_ = newNode;
    }
    else
    {
       PQNode<T> * temp = head_;
       while((temp->next != NULL) && (temp->next->priority < priority))
       {
           temp = temp->next;
       }
       newNode->next = temp->next;
       temp->next = newNode;
    }
}

template<typename T>
T PQList<T>::peek()
{
    T result;
    if(head_ == NULL)
    {
        result = T();
    }
    else
    {
        result = (head_->data);
    }
    return result;
}

template<typename T>
T PQList<T>::pop()
{
    if(head_ == NULL)
    {
        return T();
    }
    T result = head_->data;
    PQNode<T> * temp = head_;
    head_ = head_->next;
    delete(temp);
    return result;
}
} //namespace wsl

#endif //PQLIST_HPP
