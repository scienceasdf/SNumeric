#include <iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include<string>
#include<E:\eigen\Eigen/Dense>
#include<E:\eigen\Eigen/LU>
#include<E:\eigen\Eigen/Eigenvalues>

typedef Eigen::Matrix<double,3,1> vec3;
typedef Eigen::Matrix<double,3,3> mat33;

const double radPerDeg=3.141592653589793/180.0;

mat33 crossProductMat(const vec3& vec)
{
    mat33 mat;
    mat<<.0,-vec(2),vec(1),
        vec(2),.0,-vec(0),
        -vec(1),vec(0),.0;
    return mat;
}

mat33 getMatrix(vec3 vec, double alpha)
{
    mat33 res;

    vec.normalize();
    mat33 E=crossProductMat(vec);
    //std::cout<<vec.transpose()<<"\n";
    res=cos(alpha)*mat33::Identity()+(1-cos(alpha))*vec*vec.transpose()-sin(alpha)*E;
    return res;
}

void print(vec3& vec)
{
    std::cout<<vec(0)<<"i+"<<vec(1)<<"j+"<<vec(2)<<"k\t";
}

double length(vec3& vec)
{
    return pow(vec(0)*vec(0)+vec(1)*vec(1)+vec(2)*vec(2),.5);
}

int main()
{
    mat33 tensor;
    mat33 tensor_;
    tensor<<180.0,.0,.0,
            .0,10.0,.0,
            .0,.0,12.0;



    vec3 omega;
    vec3 omega_;
    vec3 ome;
    vec3 pre_omega;



    vec3 angularM;
    /*angularM<<0,0,30;
    vec3 v1;
    v1<<1,0,0;

    mat33 temp=getMatrix(v1,20*radPerDeg);
    std::cout<<temp<<"\n";
    tensor=temp.transpose()*tensor*temp;
    omega=tensor.inverse()*angularM;*/
    omega<<12.0,.1,.1;
    pre_omega=omega;
    angularM=tensor*omega;

    double t=.0,dt=.001;

    mat33 A;

    print(omega);
    print(angularM);
    std::cout<<"\n";
    std::cout<<omega.transpose()*tensor*omega<<"\n";
    for(int i=0;i<50;++i){


        //ome=1.5*omega-.5*pre_omega;
        ome=omega;

        A=getMatrix(ome,length(ome)*dt);
        //std::cout<<A<<"\n";
        tensor_=A.transpose()*tensor*A;
        omega_=tensor_.inverse()*angularM;
        ome=.5*omega+.5*omega_;

        A=getMatrix(ome,length(ome)*dt);
        tensor=A.transpose()*tensor*A;

        pre_omega=omega;
        omega=tensor.inverse()*angularM;

        //std::cout<<tensor<<"\n";
        print(pre_omega);
        print(omega);

        //print(angularM);
        std::cout<<omega.transpose()*tensor*omega<<"\n";
        t+=dt;

    }
    std::cout<<omega.transpose()*tensor*omega<<"\n";

    /*vec3 vec(2.0/7.0,3.0/7.0,6.0/7.0);
    mat33 m2=getMatrix(vec,30*radPerDeg);
    mat33 m;
    m<<.9363,.3130,-.1593,
        -.2896,.9447,.1540,
        .1987,-.0981,.9751;
    auto res=m*m2;
    std::cout<<res;*/

    return 0;
}
