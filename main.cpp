#include <iostream>
#include <list>
#include <iomanip>
#include <random>

using namespace std;

void PrintList(list<float> & LST)
{
    for (list<float>::iterator lt = LST.begin(); lt != LST.end(); ++lt)
    {
        cout << *(lt) << " ";
    }
    cout << endl;
}

void AverageAndPush(list<float> & LST)
{
    float sum = 0;
    for (list<float>::iterator lt = LST.begin(); lt != LST.end(); ++lt)
    {
        sum += *(lt);
    }
    LST.push_back(sum/LST.size());
}

    template <class InputIterator, class Distance>
    void advance (InputIterator& it, Distance n); 

void HomeWork_1()
{
    cout << "Home Work #1" << endl;
    //соберем список
    list<float> List{2, 3, 4, 5, 6, 7, 8, 9};
    cout << "Original list : ";
    PrintList(List);
    AverageAndPush(List);
    cout << "Modifed list  : ";
    PrintList(List);
    cout << endl;
}

class matrix
{
private:
    int Size;
    int ** pt_array = nullptr;

    void getMatrixWithOne(int ** mat, int ** newMat, int size, int row, int cow) const
    {
        int offsetRow = 0;
        int offsetCow = 0;
        for (size_t i = 0; i < size - 1; ++i)
        {
            if (i == row)
            {
                offsetRow = 1;
            }

            offsetCow = 0;
            for (size_t k = 0; k < size - 1; ++k)
            {
                if (k == cow)
                {
                    offsetCow = 1;
                }
                newMat[i][k] = mat[i + offsetRow][k + offsetCow];
            }
        }
    }
    int matrixDet(int ** mat, int size) const
    {
        int det = 0;
        int degree = 1;
        if (size == 1)
        {
            return mat[0][0];
        }
        else if (size == 2)
        {
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        }
        else
        {
            int ** newMat = new int * [size - 1];
            for (size_t i = 0; i < size - 1; ++i)
            {
                newMat[i] = new int[size - 1];
            }

            for (size_t i = 0; i < size; ++i)
            {
                getMatrixWithOne(mat, newMat, size, 0, i);
                det = det + (degree * mat[0][i] * matrixDet(newMat, size - 1));
                degree = -degree;
            }

            for (size_t i = 0; i < size - 1; ++i)
            {
                delete [] newMat[i];
            }
            delete [] newMat;

            return det;
        }
    }
    
public:
    matrix(int size) : Size(size)
    {
        //создаем массив
        //он квадратный, так детерминатор применим только к квадратным матрицам
        pt_array = new int * [Size];
        for (size_t i = 0; i < Size; ++i)
        {
            pt_array[i] = new int [Size];
        }
        //заполняем рандомом матрицу
        random_device random_device;
        mt19937 generator(random_device());
        uniform_int_distribution<> distribution(1, 100);
        for (size_t i = 0; i < Size; ++i)
        {
            for (size_t n = 0; n < Size; ++n)
            {
                pt_array[i][n] = distribution(generator);
            }
        }
    }
    
    ~matrix()
    {
        //высвобождаем память
        for (size_t i = 0; i < Size; ++i)
        {
            delete [] pt_array[i];
        }
        delete [] pt_array;
    }
    
    friend ostream& operator<<(ostream &out, const matrix &m);  

    int GetDet() const
    {
        //специально вынес matrixDet в привате, что бы не смущать пользователя класса параметрами
        return matrixDet(pt_array, Size);
    }
};

ostream& operator<<(ostream &out, const matrix &m)
{
    out << "Matrix: " << m.Size << "x" << m.Size << endl;
    for (size_t i = 0; i < m.Size; ++i)
    {
        for (size_t n = 0; n < m.Size; ++n)
        {
            out << setw(4) << setprecision(2) << m.pt_array[i][n] << " ";
        }
        out << endl;
    }
    return out;
}
void HomeWork_2()
{
    cout << "Home Work #2" << endl;
    matrix M(10);
    cout << M;
    cout << "Determinant: " << M.GetDet() << endl;
    cout << endl;
}

template<typename T>
class OtherInterator;

template<typename T>
class Container
{
private:
    size_t size;
    T * data;
public:
    typedef OtherInterator<T> iterator;
    Container(size_t value);
    ~Container();
    iterator begin();
    iterator end();
    T & operator[] (const size_t N);
};

template <typename T>
inline Container<T>::Container(size_t value) : size(value)
{
    data = new T[value];
}

template<typename T>
inline Container<T>::~Container()
{
    delete [] data;
}

template<typename T>
inline typename Container<T>::iterator Container<T>::begin()
{
	return data;
}

template<typename T>
inline typename Container<T>::iterator Container<T>::end()
{
	return data + size;
}

template <typename T>
inline T & Container<T>::operator[] (const size_t N)
{
    return data[N];
}

template <typename T>
class OtherInterator : public iterator<input_iterator_tag, T>
{
    friend class Container<T>;
private:
    OtherInterator(T * p);
public:
    OtherInterator(const OtherInterator & it);
    bool operator!=(OtherInterator const & other) const;
    bool operator==(OtherInterator const & other) const;
    T & operator*() const;
    OtherInterator & operator++();
private:
    T * p;
};

template <typename T>
inline OtherInterator<T>::OtherInterator(T * p) : p(p) {}

template <typename T>
inline OtherInterator<T>::OtherInterator(const OtherInterator & it) : p(it.p) {}

template<typename T>
inline bool OtherInterator<T>::operator!=(OtherInterator const & other) const
{
    return p != other.p;
}

template<typename T>
inline bool OtherInterator<T>::operator==(OtherInterator const & other) const
{
    return p == other.p;
}

template<typename T>
inline OtherInterator<T> & OtherInterator<T>::operator++()
{
    ++p;
    return * this;
}

template<typename T>
inline T & OtherInterator<T>::operator*() const
{
    return *p;
}

void HomeWork_3()
{
    cout << "Home Work #3" << endl;
    Container<int> C(5);
    C[0] = 1;
    C[1] = 2;
    C[2] = 3;
    C[3] = 4;
    C[4] = 5;
    for (auto number : C) {
        cout << number << " ";
    }

    cout << endl;
}

int main ()
{
    //HomeWork_1();
    //HomeWork_2();
    HomeWork_3();
    return 0;
}