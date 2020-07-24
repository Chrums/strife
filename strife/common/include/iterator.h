#pragma once

namespace strife {
    namespace common {
        
        template <class T, class U>
        class IIterator {
            
        public:
        
            IIterator() = default;
            virtual ~IIterator() = default;
            
            virtual T& operator++() = 0;
            virtual T& operator++(int) = 0;
            virtual bool operator==(const T& iterator) const = 0;
            virtual bool operator!=(const T& iterator) const = 0;
            virtual U operator*() const = 0;
            
        };

    }
}