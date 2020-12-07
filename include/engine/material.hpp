#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <glm/glm.hpp>

class Material {
    public:
        enum class Type {
            gem = 0,
            stone = 1,
            metal = 2,
            plastic = 3,
            rubber = 4
        };

        enum class Gem {
            emerald = 1,
            ruby = 2
        };

        enum class Stone {
            jade = 1,
            obsidian = 2,
            pearl = 3,
            turquoise = 4
        };

        enum class Metal {
            brass = 1,
            bronze = 2,
            chrome = 3,
            copper = 4,
            gold = 5,
            silver = 6
        };

        enum class Color {
            black = 1,
            white = 2,
            red = 3,
            green= 4,
            yellow = 5,
            cyan = 6
        };

        Material(Type type, Gem gem, Stone stone, Metal metal, Color plastic, Color rubber);

    private:            
        void assignGem(Gem gem);
        void assignStone(Stone stone);
        void assignMetal(Metal metal);
        void assignPlastic(Color colorP);
        void assignRubber(Color colorR);

    private:
        glm::vec3 _ambient, _diffuse, _specular;
        float _shininess;
};

#endif