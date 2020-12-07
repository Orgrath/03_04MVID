#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <glm/glm.hpp>

class Material {
    public:
        enum class Type {
            plastic = 0,
            rubber = 1
        };

        enum class Gem {
            emerald = 0,
            ruby = 1
        };

        enum class Stone {
            jade = 0,
            obsidian = 1,
            pearl = 2,
            turquoise = 3
        };

        enum class Metal {
            brass = 0,
            bronze = 1,
            chrome = 2,
            copper = 3,
            gold = 4,
            silver = 5
        };

        enum class Color {
            black = 0,
            white = 1,
            red = 2,
            green= 3,
            yellow = 4,
            cyan = 5
        };

        Material(Gem gem);
        Material(Stone stone);
        Material(Metal metal);
        Material(Type type, Color color);

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