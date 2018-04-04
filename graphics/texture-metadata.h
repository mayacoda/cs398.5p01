
#ifndef DZ04_TEXTURE_METADATA_H
#define DZ04_TEXTURE_METADATA_H


#include <string>
#include <iostream>

struct TextureMetadata {
    int         flag;
    std::string extension;

    enum terrainPosition {
        edge        = 0x0001,
        top         = 0x0002,
        bottom      = 0x0004,
        left        = 0x0008,
        right       = 0x0010,
        corner      = 0x0020,
        innerCorner = 0x0040,
        full        = 0x0080,
        none        = 0x0100,
        water       = 0x0200,
        mountains   = 0x0400,
        forest      = 0x0800,
    };


    void set(int f) {
        flag |= f;
    }

    bool is(terrainPosition f) {
        return (flag & f) != 0;
    }

    void parseTextureMatrix(int matrix[][3]) {
        std::string name;

//        std::cout << std::endl;
//        std::cout << "[" << matrix[0][0] << "  " << matrix[0][1] << "  " << matrix[0][2] << "]" << std::endl;
//        std::cout << "[" << matrix[1][0] << "  " << matrix[1][1] << "  " << matrix[1][2] << "]" << std::endl;
//        std::cout << "[" << matrix[2][0] << "  " << matrix[2][1] << "  " << matrix[2][2] << "]" << std::endl;
        // full
        if (matrix[0][0] && matrix[0][1] && matrix[0][2] &&
            matrix[1][0] && /*matrix[1][1]*/ matrix[1][2] &&
            matrix[2][0] && matrix[2][1] && matrix[2][2]) {
//            std::cout << "full" << std::endl;
            name = "f";
            set(full | left | right | top | bottom);
        }

        //c1
        if (!matrix[0][0] && !matrix[0][1] && /*matrix[0][2]*/
            !matrix[1][0] && /*matrix[1][1]*/ matrix[1][2] &&
            /* matrix[2][0] */ matrix[2][1] /*matrix[2][2]*/) {
            name = "c3";
//            std::cout << "corner right bottom" << std::endl;
            set(corner | right | bottom);
        }

        //c2
        if (/*matrix[0][0]*/  !matrix[0][1] && !matrix[0][2] &&
            matrix[1][0] && /*matrix[1][1]*/ !matrix[1][2] &&
            /*matrix[2][0]*/  matrix[2][1]  /*matrix[2][2]*/) {
            name = "c2";
//            std::cout << "corner left bottom" << std::endl;
            set(corner | left | bottom);
        }

        //c3
        if (/*matrix[0][0]*/ matrix[0][1] && /*matrix[0][2]*/
            matrix[1][0] && /*matrix[1][1]*/ !matrix[1][2] &&
            /*matrix[2][0]*/ !matrix[2][1] && !matrix[2][2]) {

            name = "c1";
//            std::cout << "corner top left" << std::endl;
            set(corner | top | left);
        }

        //c4
        if (/*matrix[0][0]*/ matrix[0][1] && /*matrix[0][2]*/
            !matrix[1][0] && /*matrix[1][1]*/ matrix[1][2] &&
            !matrix[2][0] && !matrix[2][1]  /*matrix[2][2]*/) {
            name = "c4";
//            std::cout << "corner top right" << std::endl;
            set(corner | top | right);
        }

        //e2
        if (/*matrix[0][0]*/ matrix[0][1] && /*matrix[0][2] &&*/
            matrix[1][0] && /*matrix[1][1]*/ matrix[1][2] &&
            /*!matrix[2][0] &&*/ !matrix[2][1] /*&& !matrix[2][2]*/) {
            name = "e2";
//            std::cout << "edge top" << std::endl;
            set(edge | top);
        }

        // e1
        if (/*!matrix[0][0] &&*/ matrix[0][1] && /*matrix[0][2] &&*/
            !matrix[1][0] && /*matrix[1][1]*/ matrix[1][2] &&
            /*!matrix[2][0] &&*/ matrix[2][1] /*matrix[2][2]*/) {
            name = "e1";
//            std::cout << "edge right" << std::endl;
            set(edge | right);
        }

        // e4
        if (/*!matrix[0][0] &&*/ !matrix[0][1] && /*!matrix[0][2] &&*/
            matrix[1][0] && /*matrix[1][1]*/ matrix[1][2] &&
            /*matrix[2][0] &&*/ matrix[2][1] /*matrix[2][2]*/) {
            name = "e4";
//            std::cout << "edge bottom" << std::endl;
            set(edge | bottom);
        }

        // e3
        if (/*matrix[0][0] &&*/ matrix[0][1] && /*!matrix[0][2] &&*/
            matrix[1][0] && /*matrix[1][1]*/ !matrix[1][2] &&
            /*matrix[2][0] &&*/ matrix[2][1] /*&& !matrix[2][2]*/) {
            name = "e3";
//            std::cout << "edge left" << std::endl;
            set(edge | left);
        }

        // i1
        if (matrix[0][0] && matrix[0][1] && !matrix[0][2] &&
            matrix[1][0] && /*matrix[1][1]*/ matrix[1][2] &&
            /*matrix[2][0]*/ matrix[2][1] && matrix[2][2]) {
            name = "i1";
            set(innerCorner | top | right);
//            std::cout << "inner top right" << std::endl;
        }

        // i2
        if (/*matrix[0][0]*/ matrix[0][1] && matrix[0][2] &&
             matrix[1][0] && /*matrix[1][1]*/ matrix[1][2] &&
             matrix[2][0] && matrix[2][1] && !matrix[2][2]) {
            name = "i4";
//            std::cout << "inner bottom right" << std::endl;
            set(innerCorner | bottom | right);
        }

        // i3
        if (matrix[0][0] && matrix[0][1] && /*matrix[0][2]*/
            matrix[1][0] && /*matrix[1][1]*/ matrix[1][2] &&
            !matrix[2][0] && matrix[2][1] && matrix[2][2]) {
            name = "i3";
//            std::cout << "inner bottom left" << std::endl;
            set(innerCorner | bottom | left);
        }

        // i4
        if (!matrix[0][0] && matrix[0][1] && matrix[0][2] &&
            matrix[1][0] && /*matrix[1][1]*/ matrix[1][2] &&
            matrix[2][0] && matrix[2][1]  /*matrix[2][2]*/) {
            name = "i2";
//            std::cout << "inner top left" << std::endl;
            set(innerCorner | top | left);
        }


        if (name.empty()) {
            name = "f";
//            std::cout << "UNNAMED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        }

        extension = name;
    }

    bool operator==(const TextureMetadata &rhs) const {
        return flag == rhs.flag;
    }

    bool operator!=(const TextureMetadata &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const TextureMetadata &rhs) const {
        return flag < rhs.flag;
    }

    bool operator>(const TextureMetadata &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const TextureMetadata &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const TextureMetadata &rhs) const {
        return !(*this < rhs);
    }
};

#endif //DZ04_TEXTURE_METADATA_H
