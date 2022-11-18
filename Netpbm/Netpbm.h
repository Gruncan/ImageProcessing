

#ifndef IMAGEPROCESSING_NETPBM_H
#define IMAGEPROCESSING_NETPBM_H

#include <cstdlib>

namespace Netpbm {


    class Netpbm {
    private:
        int *imageArray;
        int height;
        int width;
        int n;
        int VERSION_N: 4;
    public:
        Netpbm(int width, int height, int version) {
            this->imageArray = (int *) malloc(height * width * sizeof(int));

            this->height = height;
            this->width = width;
            this->n = height * width;
            this->VERSION_N = version;
        }

        [[nodiscard]] int getWidth() const {
            return this->width;
        }

        [[nodiscard]] int getHeight() const {
            return this->height;
        }

        [[nodiscard]] int getVersion() const {
            return this->VERSION_N;
        }

        int *getImageArray() {
            return this->imageArray;
        }

        void operator+(int const scaler) {
            for (int i = 0; i < this->n; i++) {
                this->imageArray[i] += scaler;
            }
        }

        void setImageArray(const int array[]) {
            for (int i = 0; i < this->n; ++i) {
                this->imageArray[i] = array[i];
            }
        }

        [[nodiscard]] std::string getImageArrayString() const {
            std::string s = "[";
            for (int i = 0; i < this->n; ++i) {
                if (i % this->height == 0 && i != 0)
                    s += "]\n[";

                s += std::to_string(this->imageArray[i]);
                s += " ";
            }
            s += "]";
            return s;
        }

        friend std::ostream &operator<<(std::ostream &os, Netpbm const &pbm) {
            return os << pbm.getImageArrayString();
        }

        int &operator[](int i) {
            return this->imageArray[i];
        }

        int &operator()(int i, int j) {
            return this->imageArray[(this->height * i) + j];
        }


        virtual int getColour() = 0;


    };


}


#endif //IMAGEPROCESSING_NETPBM_H
