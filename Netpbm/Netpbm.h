

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


        Netpbm(unsigned int width, unsigned int height, unsigned int version, unsigned int colour);

        explicit Netpbm(unsigned int version);

    public:
        [[nodiscard]] unsigned int getWidth() const;

        [[nodiscard]] unsigned int getHeight() const;

        [[nodiscard]] unsigned int getVersion() const;

        unsigned int *getImageArray();

        Netpbm *operator+(int const scaler);

        Netpbm *operator+(const Netpbm &vector);

        Netpbm *operator%(unsigned int const scaler);

        Netpbm *operator*(unsigned int const scaler);

        Netpbm *operator!=(unsigned int const scaler);

        void operator~();

//      TODO Added to CPP file
        friend std::ostream &operator<<(std::ostream &os, Netpbm const &pbm) {
            return os << pbm.getImageArrayString();
        }

        unsigned int &operator[](int i);

        unsigned int &operator()(int i, int j);

        void setImageArray(const unsigned int array[]);

        void setWidth(unsigned int w);

        void setHeight(unsigned int h);

        void __setN();

        [[nodiscard]] std::string getImageArrayString() const;

        virtual void invertImage();

        void copy(Netpbm &target);

        [[nodiscard]] unsigned int getMaxColour() const;

        void setMaxColour(unsigned int c);

        virtual bool exportImageBody(std::ofstream &outimage) = 0;

        virtual bool exportImageHeader(std::ofstream &outImage) = 0;

        virtual bool importImageBody(std::vector<std::string> &inFile) = 0;

        virtual bool importImageHeader(std::vector<std::string> &inFile) = 0;

        ~Netpbm();


    protected:
        static std::list<unsigned int> string_split(const std::string &str);

    };



    bool exportImage(Netpbm &image, const std::string &filename);

    void importImageInto(Netpbm &pbm, const std::string &filename);


}


#endif //IMAGEPROCESSING_NETPBM_H
