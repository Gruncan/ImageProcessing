

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


        bool exportImageBody(std::ofstream &outImage) override {
            for (int i = 0; i < this->width * this->height; ++i) {
                outImage << PPM::fromHexToString(this->imageArray[i]) << std::endl;
            }
            return true;
        }

        bool exportImageHeader(std::ofstream &outImage) override {
            outImage << "P" << this->VERSION_N << std::endl;
            outImage << this->width << " " << this->height << std::endl;
            outImage << this->colour << std::endl;
            return true;
        }

        bool importImageBody(std::vector<std::string> &body) override {
            if (body.size() != this->width * this->height) return false;

            this->imageArray = (unsigned int *) malloc(this->width * this->height * sizeof(unsigned int));
            for (int i = 0; i < this->width * this->height; ++i) {
                this->imageArray[i] = PPM::fromStringToHex(body[i]);
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

        void invertImage() override {
            for (int i = 0; i < this->n; ++i) {
                std::vector<unsigned int> vec = PPM::fromHexToVec(this->imageArray[i]);
                this->imageArray[i] = PPM::fromVecToHex(
                        {this->colour - vec[0], this->colour - vec[1], this->colour - vec[2]});
            }
        }

        static unsigned int fromVecToHex(std::vector<unsigned int> vec) {
            unsigned int v1 = vec[0];
            unsigned int v2 = vec[1];
            unsigned int v3 = vec[2];

            unsigned int value = v3 << 8;
            value |= v2;
            value <<= 8;
            value |= v1;

            return value;
        }

        static std::vector<unsigned int> fromHexToVec(unsigned int i) {
            unsigned int v1 = i & 0x0000FF;
            unsigned int v2 = (i & 0x00FF00) >> 8;
            unsigned int v3 = (i & 0xFF0000) >> 16;

            std::vector<unsigned int> vec = {v1, v2, v3};

            return vec;
        }

        static std::string fromHexToString(unsigned int i) {
            unsigned int v1 = i & 0x0000FF;
            unsigned int v2 = (i & 0x00FF00) >> 8;
            unsigned int v3 = (i & 0xFF0000) >> 16;

            std::stringstream stream;
            stream << v1 << " " << v2 << " " << v3;

            return stream.str();
        }

        static unsigned int fromStringToHex(const std::string &line) {
            std::list<unsigned int> split = Netpbm::Netpbm::string_split(line);
            unsigned int v1 = split.front();
            split.pop_front();
            unsigned int v2 = split.front();
            split.pop_front();
            unsigned int v3 = split.front();

            unsigned int value = v3 << 8;
            value |= v2;
            value <<= 8;
            value |= v1;

            return value;
        }
    };


}


#endif //IMAGEPROCESSING_PPM_H
