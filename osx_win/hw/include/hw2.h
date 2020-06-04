#ifndef __HW2__
#define __HW2__

#include <stdlib.h>
#include "hw1.h"
#include <time.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <typeinfo>

class CameraImage;


using namespace std;

namespace imageSpace{

  template<typename T>
    class Image{
    protected:
        int height;
        int width;


    public:
      friend ostream &operator<<(std::ostream& os, const CameraImage& e);
      vector<T> local_buffer;
      friend bool operator ==(CameraImage& first, CameraImage& second);

      //friend bool operator==(CameraImage& first, CameraImage& second);
      bool operator >(CameraImage& ref);
      bool operator !=(CameraImage& ref);
        Image(){}
        Image(int x, int y): height(y), width(x){}
        Image(vector<T> &copy_from, int x, int y)
         : height(y), width(x)
        {
          local_buffer.resize(x*y*3);
          for(uint i=0; i<copy_from.size(); ++i){
          local_buffer[i] = copy_from[i];
          }
        }

        virtual ~Image(){}

        virtual void populate_image() = 0;
        virtual void print_image() = 0;
        virtual void average_image() = 0;
        virtual void invert_image() = 0;
        virtual T *index_image(int x_val, int y_val) = 0;
        virtual void replace_in_image(T* start, char color, int value) = 0;
        virtual void flip_image() = 0;
        virtual void copy_from(vector<T> &copy_from) = 0;
    };


  template <typename T>
    class CameraImage: public Image<T>{
    public:

        CameraImage() : Image<T>(){}
        CameraImage(int x, int y) : Image<T>(x,y){}
        CameraImage(vector<T> &copy_from, int x, int y) : Image<T>(copy_from, x,y){}

        // Overloaded << Operator;

        friend ostream &operator<<(std::ostream& os, const CameraImage& e){
          vector<T> v = e.local_buffer;
          for(auto const& value: v) {
            os << value;
          }
          return os;
        }

        virtual ~CameraImage(){}

        virtual void populate_image(){
            hw::populate_vector(this->local_buffer);
        }

        virtual void print_image(){
            hw::print_vector(this->local_buffer, this->width, this->height);
        }

        virtual void average_image(){
            hw::average_vector(this->local_buffer);
        }

        virtual void invert_image(){
            hw::invert_vector(this->local_buffer);
        }

        virtual T *index_image(int x_val, int y_val){
            return hw::index_vector(this->local_buffer, this->width, this->height, x_val, y_val);
        }

        virtual void replace_in_image(T *start, char color, int value){
            hw::replace_in_vector(this->local_buffer, this->width, this->height, start, color, value);
        }

        virtual void flip_image(){
            hw::flip_vector(this->local_buffer, this->width, this->height);
        }

        virtual void copy_from(vector<T> &copy_from){
            hw::copy_vector(this->local_buffer, copy_from);
        }

        // Overloaded > and != Operators;

        bool operator >(CameraImage& ref){
          if (typeid(ref.local_buffer) == typeid(this->local_buffer)){
            vector<T> RHS = ref.local_buffer;
            vector<T> LHS = this->local_buffer;

            T x_index = 0;
            T averageRHS = 0;

            // Calculates RHS

            for (typename vector<T>::iterator i = RHS.begin(); i<RHS.end(); ++i){
              x_index++;

              if(x_index==3){
                  averageRHS = (*(i-2) + *(i-1) + *i)/3;
                  *(i-2) = averageRHS;
                  *(i-1) = averageRHS;
                  *i = averageRHS;
                  x_index = 0;
              }

            }

            T y_index = 0;
            T averageLHS = 0;

            // Calculates RHS

            for (typename vector<T>::iterator j = LHS.begin(); j<LHS.end(); ++j){
              y_index++;

              if(y_index==3){
                  averageLHS = (*(j-2) + *(j-1) + *j)/3;
                  *(j-2) = averageLHS;
                  *(j-1) = averageLHS;
                  *j = averageLHS;
                  y_index = 0;
              }

            }

            // Determines LHS > RHS

            if (averageLHS > averageRHS){
              return true;
            }
            else{
              return false;
            }

          }
          else{
            cout << "OMG2!";
            return false;


          }



        }

        bool operator !=(CameraImage& ref){
          if (typeid(ref.local_buffer) == typeid(this->local_buffer)){
            vector<T> RHS = ref.local_buffer;
            vector<T> LHS = this->local_buffer;
            if (RHS == LHS){
              return false;
            }
            else{
              return true;
            }
          }
          return false;
        }

      };

      // THIS IS THE OPERATOR OVERLOADING FOR == , I COULDN't GET it to
      // work in the desired way but here's the code.

/*
        bool operator ==(CameraImage<int>& first, CameraImage<uint8_t>& second){
          vector<uint8_t> RHS = second.local_buffer;
          vector<int> LHS = first.local_buffer;

          cout << RHS <<" " << LHS << "\n";

          for (typename vector<int>::iterator i = LHS.begin(); i<LHS.end(); ++i){
            if ((int) RHS.get(i) != (int) LHS.get(i)){
              return false;
            }
          }
          return true;
        }


        bool operator ==(CameraImage<uint8_t>& first, CameraImage<int>& second){
          vector<int> RHS = second.local_buffer;
          vector<uint8_t> LHS = first.local_buffer;

          cout << RHS <<" " << LHS;

          for (typename vector<int>::iterator i = LHS.begin(); i<LHS.end(); ++i){
            if ((int) LHS.get(i) != (int) RHS.get(i)){
              return false;
            }
          }
          return true;
        }

*/








}




#endif
