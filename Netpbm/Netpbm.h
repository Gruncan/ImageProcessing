

#ifndef IMAGEPROCESSING_NETPBM_H
#define IMAGEPROCESSING_NETPBM_H

#include <cstdlib>
#include <fstream>
#include <list>
#include <vector>
#include <sstream>


namespace Netpbm {

    class Netpbm {

    protected:
        unsigned int *imageArray;
        unsigned int height;
        unsigned int width;
        unsigned int n;
        unsigned int colour;
        unsigned int VERSION_N;


        Netpbm(unsigned int width, unsigned int height, unsigned int version, unsigned int colour) {
            this->imageArray = (unsigned int *) malloc(height * width * sizeof(unsigned int));

            this->height = height;
            this->width = width;
            this->n = height * width;
            this->VERSION_N = version;
            this->colour = colour;
        }

        explicit Netpbm(unsigned int version) {
            this->imageArray = nullptr;
            this->height = -1;
            this->width = -1;
            this->n = -1;
            this->VERSION_N = version;
            this->colour = -1;
        }

    public:
        [[nodiscard]] unsigned int getWidth() const {
            return this->width;
        }

        [[nodiscard]] unsigned int getHeight() const {
            return this->height;
        }

        [[nodiscard]] unsigned int getVersion() const {
            return this->VERSION_N;
        }

        unsigned int *getImageArray() {
            return this->imageArray;
        }

        Netpbm *operator+(int const scaler) {
            for (int i = 0; i < this->n; i++) {
                this->imageArray[i] = (this->imageArray[i] + scaler) % this->getMaxColour();
            }
            return this;
        }

        Netpbm *operator+(const Netpbm &vector) {
            if (this->width != vector.width || this->height != vector.height) {
                fprintf(stderr, "Unable to add vectors with sizes (%d, %d) + (%d, %d)", this->width, this->height,
                        vector.width, vector.height);
                return nullptr;
            }
            for (int i = 0; i < this->n; ++i) {
                this->imageArray[i] = (this->imageArray[i] + vector.imageArray[i]) % this->getMaxColour();
            }
            return this;
        }

        Netpbm *operator%(unsigned int const scaler) {
            for (int i = 0; i < this->n; ++i) {
                this->imageArray[i] %= scaler;
            }
            return this;
        }

        Netpbm *operator*(unsigned int const scaler) {
            for (int i = 0; i < this->n; ++i) {
                this->imageArray[i] *= scaler;
            }
            return this;
        }

        Netpbm *operator!=(unsigned int const scaler) {
            for (int i = 0; i < this->n; ++i) {
                this->imageArray[i] = this->imageArray[i] != scaler;
            }
            return this;
        }


        friend std::ostream &operator<<(std::ostream &os, Netpbm const &pbm) {
            return os << pbm.getImageArrayString();
        }

        unsigned int &operator[](int i) {
            return this->imageArray[i];
        }

        unsigned int &operator()(int i, int j) {
            return this->imageArray[(this->height * i) + j];
        }


        void setImageArray(const unsigned int array[]) {
            if (this->imageArray == nullptr) {
                if (this->width == -1 || this->height == -1) {
                    fprintf(stderr, "Invalid height or width, height: %d, width: %d\n", this->height, this->width);
                    return;
                }
                this->imageArray = (unsigned int *) malloc(this->height * this->width * sizeof(unsigned int));
            }
            for (int i = 0; i < this->n; ++i) {
                this->imageArray[i] = array[i];
            }
        }


        void setWidth(unsigned int w) {
            this->width = w;
            this->__setN();
        }

        void setHeight(unsigned int h) {
            this->height = h;
            this->__setN();
        }

        void __setN() {
            this->n = this->height * this->width;
        }

        [[nodiscard]] std::string getImageArrayString() const {
            std::string s = "[";
            for (int i = 0; i < this->n; ++i) {
                if (i % this->width == 0 && i != 0)
                    s += "]\n[";

                s += std::to_string(this->imageArray[i]);
                s += " ";
            }
            s += "]";
            return s;
        }


        virtual void invertImage() {
            unsigned int max_colour = this->getMaxColour();
            for (int i = 0; i < this->n; ++i) {
                this->imageArray[i] = (this->imageArray[i] > max_colour) ? this->imageArray[i] - max_colour :
                                      max_colour - this->imageArray[i];
            }
        }

        void copy(Netpbm &target) {
            target.width = this->width;
            target.height = this->height;
            target.n = this->n;
            target.setMaxColour(this->getMaxColour());
            target.VERSION_N = this->VERSION_N;
            target.setImageArray(this->imageArray);
        }

        [[nodiscard]] unsigned int getMaxColour() const {
            return this->colour;
        }

        void setMaxColour(unsigned int c) {
            this->colour = c;
        }

        virtual bool exportImageBody(std::ofstream &outimage) = 0;

        virtual bool exportImageHeader(std::ofstream &outImage) = 0;

        virtual bool importImageBody(std::vector<std::string> &inFile) = 0;

        virtual bool importImageHeader(std::vector<std::string> &inFile) = 0;


        ~Netpbm() {
            free(this->imageArray);
        }


    protected:
        static std::list<unsigned int> string_split(const std::string &str) {
            std::list<unsigned int> result;
            std::istringstream iss(str);
            for (int s; iss >> s;)
                result.push_back(s);

            return result;
        }

    };



    bool exportImage(Netpbm &image, const std::string &filename) {
        std::ofstream outImage;
        outImage.open(filename);

        image.exportImageHeader(outImage);

        image.exportImageBody(outImage);

        outImage.close();

        return true;
    }


    void importImageInto(Netpbm &pbm, const std::string &filename) {
        std::vector<std::string> file;
        std::ifstream inImage(filename);

        if (!inImage.is_open()) return;

        std::string line;

        while (std::getline(inImage, line)) {
            if (line.rfind('#', 0) == 0) continue;
            file.push_back(line);
        }

        pbm.importImageHeader(file);

        bool r = pbm.importImageBody(file);

        if (!r)
            fprintf(stderr, "Failed to load body of image in file %s.\n", filename.c_str());


    }


}


#endif //IMAGEPROCESSING_NETPBM_H
