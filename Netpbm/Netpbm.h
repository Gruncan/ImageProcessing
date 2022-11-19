

#ifndef IMAGEPROCESSING_NETPBM_H
#define IMAGEPROCESSING_NETPBM_H

#include <cstdlib>
#include <fstream>
#include <list>
#include <vector>
#include <sstream>


namespace Netpbm {


    class Netpbm {
    private:
        unsigned int VERSION_N: 4;
    protected:
        unsigned int *imageArray;
        unsigned int height;
        unsigned int width;
        unsigned int n;


        Netpbm(unsigned int width, unsigned int height, unsigned int version) {
            this->imageArray = (unsigned int *) malloc(height * width * sizeof(unsigned int));

            this->height = height;
            this->width = width;
            this->n = height * width;
            this->VERSION_N = version;
        }

        explicit Netpbm(unsigned int version) {
            this->imageArray = nullptr;
            this->height = -1;
            this->width = -1;
            this->n = -1;
            this->VERSION_N = version;
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

        Netpbm *operator%(int const scaler) {
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


        void invertImage() {
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

        virtual unsigned int getMaxColour() = 0;

        virtual void setMaxColour(unsigned int colour) = 0;


        ~Netpbm() {
            free(this->imageArray);
        }

    };


    bool exportImage(Netpbm &image, const std::string &filename) {
        std::ofstream outImage;
        outImage.open(filename);

        // Headers
        outImage << "P" << image.getVersion() << std::endl;
        outImage << image.getWidth() << " " << image.getHeight() << std::endl;
        unsigned int colour = image.getMaxColour();
        if (colour != -1)
            outImage << colour << std::endl;

        for (int i = 0; i < image.getWidth() * image.getHeight(); ++i) {
            if (i % image.getWidth() == 0 && i != 0)
                outImage << std::endl;

            outImage << image[i] << " ";
        }

        outImage.close();

        return true;
    }

    static std::list<int> __string_split(const std::string &str) {
        std::list<int> result;
        std::istringstream iss(str);
        for (int s; iss >> s;)
            result.push_back(s);

        return result;
    }

    void importImageInto(Netpbm &pbm, const std::string &filename) {
        std::ifstream inImage;
        inImage.open(filename);
        if (!inImage.is_open()) return;


        std::string line;

        std::list<std::string> lines = std::list<std::string>();

        std::string type;
        int width = -1;
        int height = -1;
        int colour = -1;
        unsigned int *content;
        int pos = 0;

        while (std::getline(inImage, line)) {
            if (line.rfind('#', 0) == 0) continue;

            if (type.empty()) {
                type = line;
            } else if (width == -1) {
                std::list<int> split = __string_split(line);
                width = split.front();
                split.pop_front();
                height = split.front();

                pbm.setHeight(height);
                pbm.setWidth(width);

                content = (unsigned int *) malloc(width * height * sizeof(int));
            } else if (type != "P1" && colour == -1) {
                colour = std::stoi(line);
                pbm.setMaxColour(colour);
            } else {
                std::list<int> split = __string_split(line);
                if (split.size() != width) {
                    fprintf(stderr, "Header doesn't match file content, %zu != %d\n", split.size(), width);
                    return;
                }
                int c = pos;
                for (; pos < width + c; pos++) {
                    content[pos] = split.front();
                    split.pop_front();
                }

            }
        }

        pbm.setImageArray(content);

        free(content);
        inImage.close();

    }


}


#endif //IMAGEPROCESSING_NETPBM_H
