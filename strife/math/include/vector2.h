#pragma once

namespace strife {
    namespace math {
        
        class Vector2 {

        public:

            Vector2();
            Vector2(float x, float y);
            ~Vector2() = default;
            
            float x;
            float y;

        };
        
    }
}