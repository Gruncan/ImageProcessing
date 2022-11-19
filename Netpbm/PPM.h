

#ifndef IMAGEPROCESSING_PPM_H
#define IMAGEPROCESSING_PPM_H

#include <cstddef>
#include "Netpbm.h"

namespace Netpbm {

    class PPM : public Netpbm::Netpbm {
    private:

    public:
        PPM(unsigned int width, unsigned int height, unsigned int colour) : Netpbm::Netpbm(height, width, 3, colour) {
        }

        PPM(int width, int height) : PPM(width, height, 255) {

        }

        PPM() : Netpbm::Netpbm(3) {

        }


        std::string fromHexToString(unsigned int i) {
            unsigned int v1 = i & 0x0000FF;
            unsigned int v2 = (i & 0x00FF00) >> 8;
            unsigned int v3 = (i & 0xFF0000) >> 16;

            std::stringstream stream;
            stream << v1 << " " << v2 << " " << v3;

            return stream.str();
        }

        unsigned int fromStringToHex(std::string line) {
            std::list<unsigned int> split = Netpbm::Netpbm::string_split(line);
            unsigned int v1 = split.front();
            split.pop_front();
            unsigned int v2 = split.front();
            split.pop_front();
            unsigned int v3 = split.front();

            unsigned int value = (v3 << 8);
            value |= v2;
            value <<= 8;
            value |= v1;

            return value;
        }

        bool exportImageBody(std::ofstream &outImage) override {
            for (int i = 0; i < this->width * this->height; ++i) {
                outImage << this->fromHexToString(this->imageArray[i]);
            }
            return true;
        }

        bool exportImageHeader(std::ofstream &outImage) override {
            outImage << "P" << this->VERSION_N << std::endl;
            outImage << this->width << " " << this->height << std::endl;
            outImage << this->colour;
            return true;
        }

        bool importImageBody(std::vector<std::string> &body) override {
            if (body.size() != this->width * this->height) return false;

            this->imageArray = (unsigned int *) malloc(this->width * this->height * sizeof(unsigned int));
            for (int i = 0; i < this->width * this->height; ++i) {
                this->imageArray[i] = this->fromStringToHex(body[i]);
            }
            return true;
        }

        bool importImageHeader(std::vector<std::string> &file) override {
            std::string type;
            bool width_height = false;
            bool colour = false;

            while (!colour) {
                std::string line = file.front();
                file.erase(file.begin());

                if (type.empty()) {
                    type = line;
                } else if (!width_height) {
                    std::list<unsigned int> split = Netpbm::Netpbm::string_split(line);
                    this->width = split.front();
                    split.pop_front();
                    this->height = split.front();

                    width_height = true;
                } else {
                    this->colour = std::stoi(line);
                    colour = true;
                }
            }

            this->__setN();
            return true;
        }

    };


}


#endif //IMAGEPROCESSING_PPM_H
