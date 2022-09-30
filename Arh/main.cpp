#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <vector>

const int m = 1000;
const int n = 1000;
double lNum = 10.0;

using namespace std;

template <typename T>
void Multiplication(vector<vector<T>> &matrix, vector<T> &v, vector<T> &vectorIt)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            vectorIt.push_back(matrix[i][j] * v[j]);
    }
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

template <typename T>
double test()
{
    srand(time(0));
    vector<vector<T>> matrix(m, vector<T>(0));
    vector<T> v;
    vector<T> ansver;
    double t;

    for (int i = 0; i < m; i++)
    {

        for (int j = 0; j < n; j++)
            matrix[i].push_back(rand() % 1000);

    }
    for (int j = 0; j < n; j++)
        v.push_back(rand() % 1000);

    t = wtime();
    Multiplication<T>(matrix, v, ansver);
    t = (wtime() - t) ;

    return t;
}


template <typename T>
void Math()
{
    double dispersion =0, average = 0,  deviation = 0, taskPerf = 0, absError = 0, relError = 0;
    int instructionCount = n*(m+(n-1)) + m;
    vector<double> testAr(10);
    double t = test<T>();

    for (int i = 0; i < 10; i++)
    {
        testAr[i] += test<T>();
        average += testAr[i];
    }

    for (int i = 0; i < 10; i++)
    {
        testAr[i] = test<T>();
        average += testAr[i];
        taskPerf += (instructionCount/ testAr[i]);
        dispersion += pow(testAr[i] - average, 2);
    }

    taskPerf = pow((1 / taskPerf), -1);

    deviation = sqrt (dispersion / lNum);
    average /= lNum;//среднеквадратичное отклонение
    absError = average - t;
    relError = (absError / average)*100;

    /*FILE  *file;

    file = fopen("itog.cvs", "a");
    fprintf (file, "PModel: Intel(R) Core(TM) i3-6006U CPU @ 2.00GHz \n");
    fprintf( file, "Task: multiplying a matrix by a vector OpType: -O \nOpt float\nInsCount %d \n",  insCount);
    fprintf (file, "Timer: time()\nTime: %.6f \nLNum: 10 \nAvTime: %.6f \nAbsErr: %.6f \n", t, average, absError);
    fprintf (file, "RelErr: %.6f \nTaskPer: %.2f % \n\n", relError, taskPerf);
    fclose(file);*/
    cout<<"\nInstruction Count: " << instructionCount
    << "\nTimer: time()"
    << "\nTime: " << t
    << "\nnLNum: " << lNum
    << "\nAvTime: " << average
    << "\nAbsErr: " << absError
    << "\nRelErr: " << relError
    << "\nTaskPer: " << taskPerf;
}

int main ()
{
    cout<<"\nTask: multiplying a matrix by a vector OpType: double";
    Math<double>();
    cout<<"\n\nTask: multiplying a matrix by a vector OpType: float";
    Math<float>();
    cout<<"\n\nTask: multiplying a matrix by a vector OpType: int";
    Math<int>();
    cout<<"\n\nTask: multiplying a matrix by a vector OpType: long long";
    Math<long long>();
    return 0;
}
