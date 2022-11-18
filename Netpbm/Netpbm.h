

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
        int VERSION_N: 4;
    protected:
        int *imageArray;
        unsigned int height;
        unsigned int width;
        unsigned int n;


        Netpbm(unsigned int width, unsigned int height, int version) {
            this->imageArray = (int *) malloc(height * width * sizeof(int));

            this->height = height;
            this->width = width;
            this->n = height * width;
            this->VERSION_N = version;
        }

        explicit Netpbm(int version) {
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

        [[nodiscard]] int getVersion() const {
            return this->VERSION_N;
        }

        int *getImageArray() {
            return this->imageArray;
        }

        Netpbm *operator+(int const scaler) {
            for (int i = 0; i < this->n; i++) {
                this->imageArray[i] = (this->imageArray[i] + scaler) % this->getMaxColour();
            }
            return this;
        }


        void setImageArray(const int array[]) {
            if (this->imageArray == nullptr) {
                if (this->width == -1 || this->height == -1) {
                    fprintf(stderr, "Invalid height or width, height: %d, width: %d\n", this->height, this->width);
                    return;
                }
                this->imageArray = (int *) malloc(height * width * sizeof(int));
            }
            for (int i = 0; i < this->n; ++i) {
                this->imageArray[i] = array[i];
            }
        }


        void setWidth(unsigned int width) {
            this->width = width;
            this->__setN();
        }

        void setHeight(unsigned int height) {
            this->height = height;
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

        friend std::ostream &operator<<(std::ostream &os, Netpbm const &pbm) {
            return os << pbm.getImageArrayString();
        }

        int &operator[](int i) {
            return this->imageArray[i];
        }

        int &operator()(int i, int j) {
            return this->imageArray[(this->height * i) + j];
        }

        void invertImage() {
            int max_colour = this->getMaxColour();
            for (int i = 0; i < this->n; ++i) {
                this->imageArray[i] = abs(this->imageArray[i] - max_colour);
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

        virtual int getMaxColour() = 0;

        virtual void setMaxColour(int colour) = 0;


    };


    bool exportImage(Netpbm &image, const std::string &filename) {
        std::ofstream outImage;
        outImage.open(filename);

        // Headers
        outImage << "P" << image.getVersion() << std::endl;
        outImage << image.getWidth() << " " << image.getHeight() << std::endl;
        int colour = image.getMaxColour();
        if (colour != 0)
            outImage << colour << std::endl;

        for (int i = 0; i < image.getWidth() * image.getHeight(); ++i) {
            if (i % image.getHeight() == 0 && i != 0)
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
        int *content;
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

                content = (int *) malloc(width * height * sizeof(int));
            } else if (colour == -1) {
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
