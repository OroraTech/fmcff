/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "generic/abort.hpp"
#include <atomic>
#include <utility>
#include <cstdio>

namespace ot {

/**
 * @defgroup shared_resource Shared single-owned resources
 * @brief Shared resource keeping track of all references.
 * Accessing freed resources will log an error and stop the program.
 */

template <typename T>
class Ref;

/**
 * @ingroup shared_resource
 * @brief Shared resource container. Construct same as contained object, construct Ref using Shared as param.
 *
 * @tparam T The contained object type. Shared inherits it's constructor, but can also be constructed by copying/moving the object in.
 */
template <typename T>
class Shared : public T {
    friend class Ref<T>;

public:
    /**
     * @brief Shared inherits the contructors of it's contained object
     */
    using T::T;

    /**
     * @brief Shared can be constructed by copying T into it
     */
    Shared(const T& other) // NOLINT(google-explicit-constructor) implicit construction is wanted for this container
        :
        T(other) {}

    /**
     * @brief Shared can be constructed by moving T into it
     */
    Shared(T&& other) // NOLINT(google-explicit-constructor) implicit construction is wanted for this container
        :
        T(other) {}

    virtual ~Shared(); // NOLINT(cppcoreguidelines-explicit-virtual-functions,modernize-use-override) bases might or might not have virtual destructors.

    /**
     * @brief The shared resource can be copied by casting to it's contained type: Shared<T> copy { (T&) original };
     * Copying the Shared container itself is not allowed, to clarify that new Ref's have to be created.
     */
    Shared(const Shared& other) = delete;

    /**
     * @brief The shared resource can be copied by casting to it's contained type: Shared<T> copy { (T&) original };
     * Copying the Shared container itself is not allowed, to clarify that new Ref's have to be created.
     */
    Shared& operator=(const Shared& other) = delete;

    /**
     * @brief A Shared resource may be moved. This is an O(n) operation, as all references have to be updated.
     */
    Shared(Shared&& other) noexcept;

    /**
     * @brief A Shared resource may be moved. This is an O(n) operation, as all references have to be updated.
     */
    Shared& operator=(Shared&& other) noexcept;

private:
    /**
     * @brief Invalidate all reference to this Shared instance. Useful for assignment operator.
     */
    void invalidate();

    Ref<T>* refs_ = nullptr;
};

/**
 * @ingroup shared_resource
 * @brief Reference to a Shared resource. This may only be accessed as long as the Shared resource is not destructed.
 *
 * @tparam T The contained object type. The object may be accessed using get().
 */
template <typename T>
class Ref {
    friend class Shared<T>;

public:
    Ref() :
        valid_ { false } {}

    /**
     * @brief The Ref may be implicitly construced using a Shared resource of the same type.
     */
    Ref(Shared<T>& resource) // NOLINT(google-explicit-constructor) implicit construction is wanted for this container
        :
        ref_ { &resource },
        next_ { resource.refs_ } {
        if (next_ != nullptr) {
            next_->prev_ = this;
        }
        resource.refs_ = this;
    }

    ~Ref() {
        release();
    }

    Ref(const Ref& other) {
        if (other.valid_) {
            new (this) Ref(*other.ref_);
        } else {
            valid_ = false;
        }
    };

    Ref(Ref&& other) noexcept {
        move(std::forward<Ref<T>>(other));
    }

    Ref& operator=(const Ref& other) {
        if (this != &other) {
            release();
            new (this) Ref { other };
        }
        return *this;
    }

    Ref& operator=(Ref&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        release();
        move(std::forward<Ref<T>>(other));
        return *this;
    }

    /**
     * @brief Access the Ref's contained referenced object. This will log and stop the program if the Shared resource has been destructed.
     */
    T& get() {
        if (!valid_) {
            printf("Trying to access deleted shared resource through Ref");
            ot::abort();
        }
        return *ref_;
    }

    /**
     * @brief Use get() if you want better logging! Direct access to the Ref's contained referenced object. This will log and stop the program if the Shared resource has been destructed.
     */
    T* operator->() {
        return &get();
    }

    /**
     * @brief Check whether the referenced Shared object is still alive. Only if this returns true, get() will work.
     *
     * @return true if the Shared object is alive, false if it has been destructed
     */
    [[nodiscard]] bool is_valid() const {
        return valid_;
    }

    /**
     * @brief Check whether the referenced Shared object is still alive. See is_valid()
     */
    operator bool() const { // NOLINT(google-explicit-constructor) I think this should be allowed
        return is_valid();
    }

    /**
     * @brief Check whether the referenced Shared object is still alive. Inversion of operator bool()
     */
    bool operator!() const {
        return !is_valid();
    }

private:
    std::atomic<Shared<T>*> ref_ = nullptr;
    Ref* next_ = nullptr;
    Ref* prev_ = nullptr;
    bool valid_ = true;

private:
    /**
     * @brief internal function to deduplicate destructor and free before assignmnent
     */
    void release() {
        if (next_ != nullptr) {
            next_->prev_ = prev_;
        }
        if (prev_ != nullptr) {
            prev_->next_ = next_;
        }
        if (valid_ && ref_.load()->refs_ == this) {
            ref_.load()->refs_ = next_;
        }
        valid_ = false;
    }

    /**
     * @brief internal function to deduplicate copy constructor & assignment
     */
    void move(Ref&& other) {
        next_ = other.next_;
        prev_ = other.prev_;
        ref_ = other.ref_.load();
        valid_ = other.valid_;

        if (next_ != nullptr) {
            next_->prev_ = this;
        }
        if (prev_ != nullptr) {
            prev_->next_ = this;
        }
        if (valid_) {
            if (ref_.load()->refs_ == &other) {
                ref_.load()->refs_ = this;
            }
        }

        other.next_ = nullptr;
        other.prev_ = nullptr;
        other.ref_ = nullptr;
        other.valid_ = false;
    }
};

template <typename T>
void Shared<T>::invalidate() {
    while (refs_ != nullptr) {
        refs_->valid_ = false;
        refs_->ref_ = nullptr;
        refs_ = refs_->next_;
    }
}

template <typename T>
Shared<T>::~Shared() {
    invalidate();
}

template <typename T>
Shared<T>::Shared(Shared<T>&& other) noexcept :
    T(std::move((T&)other)) {
    if (&other == this) {
        return;
    }
    auto* list = other.refs_;
    while (list != nullptr) {
        list->ref_ = this;
        list = list->next_;
    }
    refs_ = other.refs_;
    other.refs_ = nullptr;
}

template <typename T>
Shared<T>& Shared<T>::operator=(Shared<T>&& other) noexcept {
    if (&other == this) {
        return *this;
    }
    this->invalidate();
    auto* list = other.refs_;
    while (list != nullptr) {
        list->ref_ = this;
        list = list->next_;
    }
    refs_ = other.refs_;
    other.refs_ = nullptr;
    this->T::operator=(std::move(other));
    return *this;
}
} // namespace ot
