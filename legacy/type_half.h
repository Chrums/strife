#pragma once

#include <cstdint>
#include <cstring>
#include <type_traits>

namespace strife {

    using TypeId = uint32_t;

    template<typename T>
    class Types
    {};

    class Type {

    public:

        inline const char* name() const {
            return name_;
        }

        inline const char* data() const {
            return (char*)(this + 1);
        }

        inline const TypeId& typeId() const {
            return *(TypeId*)(data() + sizeof(TypeId));
        }

        inline intptr_t as(intptr_t target, TypeId targetTypeId) const {
            const char* buffer = data();

            size_t index = 0;
            ptrdiff_t offset = 0;

            while (true) {
                TypeId size = *reinterpret_cast<const TypeId*>(buffer + index);
                index += sizeof(TypeId);

                for (TypeId counter = 0; counter < size; counter++, index += sizeof(TypeId))
                {
                    const TypeId& typeId = *reinterpret_cast<const TypeId*>(buffer + index);
                    if (typeId == targetTypeId) {
                        return target + offset;
                    }
                }

                offset = *reinterpret_cast<const ptrdiff_t*>(buffer + index);
                if (offset == 0) {
                    return 0;
                }

                index += sizeof(ptrdiff_t);
            }
        }

        inline bool operator==(const Type& type) const {
            return typeId() == type.typeId();
        }

	    inline bool operator!=(const Type& type) const { 
            return typeId() != type.typeId();
        }

    private:

        const char* name_;

    };

    namespace RTTI {

        template <typename T>
        inline const Type& Types()
        {
            return *Types<std::decay<typename std::remove_cv<T>::type>::type>::Find();
        }

        template <typename Derived, typename Base>
        inline Derived* DynamicCast(Base* base)
        {
            if constexpr (std::is_base_of<Derived, Base>::value) {
                return static_cast<Derived>(base);
            } else if (base) {
                return reinterpret_cast<Derived>(base->STRIFE_RTTI_DYNAMIC_CAST(Types::Find<Derived>().typeId()));
            } else {
                return nullptr;
            }
        }

        static TypeId GenerateTypeId()
        {
            // magic number that increases every time it is called
            static TypeId typeIdCounter = 0;
            return ++typeIdCounter;
        }

        template<typename Derived, typename Base>
        static ptrdiff_t ComputePointerOffset()
        {
            Derived* derivedPtr = (Derived*)1;
            Base* basePtr = static_cast<Base*>(derivedPtr);
            return (intptr_t)basePtr - (intptr_t)derivedPtr;
        }

    #pragma pack(push, 1)

        template <typename T>
        struct TypeData
        {};

        template <typename... BaseTypes>
        struct BaseTypeData
        {};

        template <typename FirstBase, typename SecondBase, typename... Next>
        struct BaseTypeData<FirstBase, SecondBase, Next...>
        {
            template<typename Derived>
            void FillBaseTypeData(ptrdiff_t aOffset, typeId_t& outHeadSize)
            {
                myFirst.template FillBaseTypeData<Derived>(ComputePointerOffset<Derived, FirstBase>(), outHeadSize);

                myOffset = ComputePointerOffset<Derived, SecondBase>();
                myNext.template FillBaseTypeData<Derived>(myOffset, mySize);
            }

            BaseTypeData<FirstBase> myFirst;
            ptrdiff_t myOffset;
            typeId_t mySize;
            BaseTypeData<SecondBase, Next...> myNext;
        };

        template <typename Base>
        struct BaseTypeData<Base>
        {
            template<typename Derived>
            void FillBaseTypeData(ptrdiff_t aOffset, typeId_t& outHeadSize)
            {
                const TypeData<Base>* baseTypeId = (TypeData<Base>*)(Types<Base>::Find()->buffer());

                // return size of head list
                outHeadSize = baseTypeId->mySize;

                const char* data = baseTypeId->GetData();
                size_t byteSize = baseTypeId->mySize * sizeof(typeId_t);

                // copy type list
                memcpy(myData, data, byteSize);

                size_t byteIndex = byteSize;
                ptrdiff_t offset = *reinterpret_cast<const ptrdiff_t*>(data + byteIndex);
                while (offset != 0)
                {
                    // fill next offset and add pointer offset
                    *reinterpret_cast<ptrdiff_t*>(myData + byteIndex) = offset + aOffset;
                    byteIndex += sizeof(ptrdiff_t);

                    // fill next size
                    const typeId_t size = *reinterpret_cast<const typeId_t*>(data + byteIndex);
                    *reinterpret_cast<typeId_t*>(myData + byteIndex) = size;
                    byteSize = size * sizeof(typeId_t);
                    byteIndex += sizeof(typeId_t);

                    // copy types
                    memcpy(myData + byteIndex, data + byteIndex, byteSize);
                    byteIndex += byteSize;

                    offset = *reinterpret_cast<const ptrdiff_t*>(data + byteIndex);
                }
            }

            // We only need the previous type data array, but not its size or end marker
            char myData[sizeof(TypeData<Base>) - sizeof(ptrdiff_t) - sizeof(typeId_t)];
        };

        template<typename Type, typename... BaseTypes>
        struct TypeDataImpl
        {
            TypeDataImpl()
            {
                myTypeId = GenerateId();
                myBaseTypeData.template FillBaseTypeData<Type>(0 /* No offset with first base */, mySize);
                mySize++; // Size is the base's size + 1 to account for current type id
                myEndMarker = 0;
            }

            const char* GetData() const { return (char*)&myTypeId; }

            typeId_t mySize;
            typeId_t myTypeId;
            BaseTypeData<BaseTypes...> myBaseTypeData;
            ptrdiff_t myEndMarker;
        };

        template<typename Type>
        struct TypeDataImpl<Type>
        {
            TypeDataImpl() : mySize(1), myTypeId(GenerateId()), myEndMarker(0) {}

            const char* GetData() const { return (char*)&myTypeId; }

            typeId_t mySize;
            typeId_t myTypeId;
            ptrdiff_t myEndMarker;
        };

        template<typename T>
        struct TypeInfoImpl
        {
            const RTTI::TypeInfo myInfo;
            const TypeData<T> myData;
        };

    #pragma pack(pop)

    }

    template <typename Derived, typename Base>
    inline Derived* rtti_dynamic_cast(Base* aBasePtr)
    {
        return DynamicCast<Derived, Base>(aBasePtr);
    }

}

#define STRIFE_RTTI_TYPEINFO(TYPE)                                                                                                         \
	template<>                                                                                                                             \
	struct Types<TYPE>                                                                                                                     \
	{                                                                                                                                      \
		static const strife::Type& Find()                                                                                                  \
		{                                                                                                                                  \
			static TypeInfoImpl<TYPE> ourInstance = {{#TYPE}, TypeData<TYPE>()};                                                           \
			return ourInstance.myInfo;                                                                                                     \
		}                                                                                                                                  \
	};                                                                                                                                     \

#define STRIFE_RTTI_REGISTER(...)                                                                                                          \
	namespace strife                                                                                                                       \
	{                                                                                                                                      \
        template<>                                                                                                                         \
        struct TypeData<STRIFE_FIRST_ARG(__VA_ARGS__)> : public TypeDataImpl<__VA_ARGS__>                                                     \
        {};                                                                                                                                \
        STRIFE_RTTI_TYPEINFO(STRIFE_FIRST_ARG(__VA_ARGS__))                                                                                      \
	}                                                                                                                                      \

#define STRIFE_RTTI_IMPL()                                                                                                                    \
                                                                                                                                           \
	virtual intptr_t STRIFE_RTTI_DYNAMIC_CAST(strife::TypeId aOtherTypeId) const                                                          \
	{                                                                                                                                      \
		typedef std::remove_pointer<decltype(this)>::type ObjectType;                                                                      \
		return strife::template Types<ObjectType>()->as((intptr_t)this, aOtherTypeId);                                        \
	}                                                                                                                                      \
	virtual const strife::Type& STRIFE_RTTI_GetType() const                                                                        \
	{                                                                                                                                      \
		typedef std::remove_pointer<decltype(this)>::type ObjectType;                                                                      \
		return strife::template Types<ObjectType>();                                                                              \
	}                                                                                                                                      \
	virtual const char* STRIFE_RTTI_GetTypeName() const { return STRIFE_RTTI_GetType()->name(); }                                         \
	virtual strife::TypeId STRIFE_RTTI_GetTypeId() const                                                                                 \
	{                                                                                                                                      \
		typedef std::remove_pointer<decltype(this)>::type ObjectType;                                                                      \
		return strife::template STRIFE_RTTI_GetType<ObjectType>()->identifier();                                                                                \
	}