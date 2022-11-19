

#ifndef IMAGEPROCESSING_PGM_H
#define IMAGEPROCESSING_PGM_H

#include <string>
#include "Netpbm.h"

namespace Netpbm {

    /**
     * F scale image going from 0-colour
     */
    class PGM : public Netpbm::Netpbm {
    private:
    public:
        PGM(unsigned int width, unsigned int height, unsigned int colour) : Netpbm::Netpbm(width, height, 2, colour) {

        }

        PGM(unsigned int width, unsigned int height) : PGM(width, height, 15) {

        }

        PGM() : Netpbm::Netpbm(2) {
            this->colour = -1;
        }


        bool exportImageBody(std::ofstream &outImage) override {
            for (int i = 0; i < this->width * this->height; ++i) {
                if (i % this->width == 0 && i != 0)
                    outImage << std::endl;

                outImage << this->imageArray[i] << " ";
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
            if (body.size() != this->height) return false;

            int c = 0;
            this->imageArray = (unsigned int *) malloc(this->width * this->height * sizeof(unsigned int));
            for (const std::string &line: body) {
                std::list<unsigned int> split = Netpbm::string_split(line);
                if (split.size() != this->width) return false;

                for (int i = c; i < c + this->width; ++i) {
                    this->imageArray[i] = split.front();
                    split.pop_front();
                }
                c += (int) this->width;
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


#endif //IMAGEPROCESSING_PGM_H
