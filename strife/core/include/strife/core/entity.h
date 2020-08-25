#pragma once

#include <map>
#include <typeindex>
#include "strife/reflection/type.h"
#include "strife/serialization/data.h"
#include "strife/unique/identifier.h"
#include "strife/unique/unique.h"

namespace strife {
    namespace core {
        
        class Scene;
        class Component;
        
        class Entity : public unique::Unique {

		public:

			using Context = std::map<const unique::Identifier, Entity&>;
            
        private:
            
            class Components {
                
            public:
            
                Components(Entity& entity);
				Components(const Components& components);
                ~Components() = default;
                
                Component& add(const reflection::Type& type);
				void remove(const reflection::Type& type);
				Component& at(const reflection::Type& type) const;
				Component* const find(const reflection::Type& type) const;
				
				template <class C>
				C& add() {
					const reflection::Type& type = reflection::Type::Of<C>();
					Component& component = add(type);
					return static_cast<C&>(component);
				};
				
				template <class C>
				void remove() {
					const reflection::Type& type = reflection::Type::Of<C>();
					remove(type);
				};
				
				template <class C>
				C& at() const {
					const reflection::Type& type = reflection::Type::Of<C>();
					Component& component = at(type);
					return static_cast<C&>(component);
				};
				
				template <class C>
				C* const find() const {
					const reflection::Type& type = reflection::Type::Of<C>();
					Component* const component = find(type);
					return static_cast<C* const>(component);
				};
                
            private:
            
                Entity& entity_;
                
            };
            
        public:
        
            const Scene& scene() const;
			Scene& scene();
			
            const Components& components() const;
			Components& components();
        
			Entity();
            Entity(const Entity& entity);
			Entity(Scene& scene);
			~Entity() = default;
			
			Entity& operator=(const Entity& entity);
			bool operator==(const Entity& entity) const;
			bool operator!=(const Entity& entity) const;

            void dispose();
			const serialization::Data serialize() const;
			void deserialize(const serialization::Data& data);

		private:

			Scene* scene_;
			Components components_;
            
        };

		void to_json(serialization::Data& data, const Entity& entity);
		void from_json(const serialization::Data& data, Entity& entity);
        
    }
}