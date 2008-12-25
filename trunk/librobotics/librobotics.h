/*
 *  File(s)     : librobotics.h (C++ header)
 *
 *  Description : The C++ Robotics Library.
 *                This file is the main part of the LibRobotics project.
 *                ( http://code.google.com/p/librobotics/ )
 *
 *  Created on  : Oct 24, 2008
 *      Author  : Mahisorn Wongphati
 *
 *  Copyright (c) <2008> <Mahisorn Wongphati>
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 */

/** Current library version */
#ifndef librobotics_version
#define librobotics_version 0.1


// Include required standard C++ headers.
//
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <cmath>
#include <ctime>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <iostream>
#include <string>


/*
 * Test/auto-set LibRobotics configuration variables
 * and include required headers.
 *
 * If you find that default configuration variables are
 * not adapted, you can override their values before including
 * the header file "librobotics.h" (using the #define directive).
 */

// Operating system configuration.
//
// Define 'librobotics_OS' to : 0 for an unknown OS (will try to minize library dependancies).
//                              1 for a Unix-like OS (Linux, Solaris, BSD, MacOSX, Irix, ...).
//                              2 for Microsoft Windows.
//
#ifndef librobotics_OS
#if defined(unix)        || defined(__unix)      || defined(__unix__) \
 || defined(linux)       || defined(__linux)     || defined(__linux__) \
 || defined(sun)         || defined(__sun) \
 || defined(BSD)         || defined(__OpenBSD__) || defined(__NetBSD__) \
 || defined(__FreeBSD__) || defined __DragonFly__ \
 || defined(sgi)         || defined(__sgi) \
 || defined(__MACOSX__)  || defined(__APPLE__) \
 || defined(__CYGWIN__)
#define librobotics_OS 1
#elif defined(_MSC_VER) || defined(WIN32)  || defined(_WIN32) || defined(__WIN32__) \
   || defined(WIN64)    || defined(_WIN64) || defined(__WIN64__)
#define librobotics_OS 2
#else
#define librobotics_OS 0
#endif
#elif !(librobotics_OS==0 || librobotics_OS==1 || librobotics_OS==2)
#error LibRobotics Library : Configuration variable 'librobotics_OS' is badly defined.
#error (valid values are '0=unknown OS', '1=Unix-like OS', '2=Microsoft Windows').
#endif

// Compiler configuration.
//
// Try to detect Microsoft VC++ compilers.
// (lot of workarounds are needed afterwards to
//  make LibRobotics working, particularly with VC++ 6.0).
//
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#pragma warning(disable:4800)
#pragma warning(disable:4804)
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_DEPRECATE 1
#define _CRT_NONSTDC_NO_DEPRECATE 1
#if _MSC_VER<1300
#define librobotics_use_visualcpp6
#define _WIN32_WINNT 0x0500
#endif
#endif

// Include OS-specific headers.
//
#if librobotics_OS==1
#include <sys/time.h>
#include <unistd.h>
#elif librobotics_OS==2
#include <windows.h>
#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif
#include <shlobj.h>
#ifdef librobotics_use_visualcpp6
#define std
#endif
#endif

// Output messages configuration.
//
// Define 'librobotics_debug' to : 0 to hide debug messages (quiet mode, but exceptions are still thrown).
//                          1 to display debug messages on standard error (stderr).
//                          2 to do as 1 + add extra warnings (may slow down the code !).
//
// Define 'librobotics_strict_warnings' to replace warning messages by exception throwns.
//
// Define 'librobotics_use_vt100' to allow output of color messages (require VT100-compatible terminal).
//

//#define librobotics_strict_warnings
//#define librobotics_use_vt100

#ifndef librobotics_debug
#define librobotics_debug 2
#elif !(librobotics_debug==0 || librobotics_debug==1 || librobotics_debug==2)
#error LibRobotics Library : Configuration variable 'librobotics_debug' is badly defined.
#error (valid values are '0=quiet', '1=stderr', '2=stderr+warnings').
#endif

// CImg configuration.
// (http://cimg.sourceforge.net)
//
// Define 'librobotics_use_cimg' to enable CImg support.
//
// Using CImg is not mandatory.
//
#ifdef librobotics_use_cimg
#include <CImg.h>
#endif

// OpenGL configuration.
// (www.opengl.org)
//
// Define 'librobotics_use_opengl' to enable OpenGL support.
//
// Using OpenGL is not mandatory.
//
#ifdef librobotics_use_opengl
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

// Some useful constants. (copy from GNU math.h)
#if !(defined __USE_BSD || defined __USE_XOPEN)
# define M_E        2.7182818284590452354   /* e */
# define M_LOG2E    1.4426950408889634074   /* log_2 e */
# define M_LOG10E   0.43429448190325182765  /* log_10 e */
# define M_LN2      0.69314718055994530942  /* log_e 2 */
# define M_LN10     2.30258509299404568402  /* log_e 10 */
# define M_PI       3.14159265358979323846  /* pi */
# define M_PI_2     1.57079632679489661923  /* pi/2 */
# define M_PI_4     0.78539816339744830962  /* pi/4 */
# define M_1_PI     0.31830988618379067154  /* 1/pi */
# define M_2_PI     0.63661977236758134308  /* 2/pi */
# define M_2_SQRTPI 1.12837916709551257390  /* 2/sqrt(pi) */
# define M_SQRT2    1.41421356237309504880  /* sqrt(2) */
# define M_SQRT1_2  0.70710678118654752440  /* 1/sqrt(2) */
#endif

/* The above constants are not adequate for computation using `long double's.
   Therefore we provide as an extension constants with similar names as a
   GNU extension.  Provide enough digits for the 128-bit IEEE quad.  */
#ifndef __USE_GNU
# define M_El       2.7182818284590452353602874713526625L  /* e */
# define M_LOG2El   1.4426950408889634073599246810018921L  /* log_2 e */
# define M_LOG10El  0.4342944819032518276511289189166051L  /* log_10 e */
# define M_LN2l     0.6931471805599453094172321214581766L  /* log_e 2 */
# define M_LN10l    2.3025850929940456840179914546843642L  /* log_e 10 */
# define M_PIl      3.1415926535897932384626433832795029L  /* pi */
# define M_PI_2l    1.5707963267948966192313216916397514L  /* pi/2 */
# define M_PI_4l    0.7853981633974483096156608458198757L  /* pi/4 */
# define M_1_PIl    0.3183098861837906715377675267450287L  /* 1/pi */
# define M_2_PIl    0.6366197723675813430755350534900574L  /* 2/pi */
# define M_2_SQRTPIl    1.1283791670955125738961589031215452L  /* 2/sqrt(pi) */
# define M_SQRT2l   1.4142135623730950488016887242096981L  /* sqrt(2) */
# define M_SQRT1_2l 0.7071067811865475244008443621048490L  /* 1/sqrt(2) */
#endif




/** \defgroup g_user_marco User-friendly macros */
/* @{ */
#define LB_IS_ZERO              (1e-8)
#define LB_VERY_SMALL           (1e-6)
#define LB_SIGN(A)              ((A) >= 0.0 ? (1.0) : (-1.0))
#define LB_SIGN_BOOL(A)         ((A) >= 0.0 ? (true) : (false))
#define LB_ROUND(x)             ((x) < 0 ? ceil((x)-0.5):floor((x)+0.5))
#define LB_SQR(x)               ((x)*(x))
#define LB_SQUARE(x)            (LB_SQR(x))
#define LB_DEG2RAD(x)           (((x)/180.0) * M_PI)
#define LB_RAD2DEG(x)           (((x)/M_PI) * 180.0)
#define LB_SIZE(x,y)            (sqrt(LB_SQR(x) + LB_SQR(y)))

//compare
#define LB_MIN(a,b)             ((a) <= (b) ? (a) : (b))
#define LB_MIN_BOOL(a,b)        ((a) <= (b) ? true : false)
#define LB_MIN3(a,b,c)          (MIN2(MIN2(a,b), c))

#define LB_MAX(a, b)            (((a) >= (b)) ? (a) : (b))
#define LB_MAX_BOOL(a, b)       (((a) >= (b)) ? true : false)
#define LB_MAX3(a, b, c)        (MAX2(MAX2(a,b), c))
/* @} */

/** \defgroup g_user_template User-friendly template functions */
/* @{ */
/**
 * Normalize the angle to \f$(-\pi, \pi)\f$ radian unit
 * \param a input angle value
 * \return normalized angle
 */
template<typename T>
T inline norm_a_rad(T a) {
    int m = (int)(a / (2.0*M_PI));
    a = a - (m * M_PI * 2.0);
    if (a < (-M_PI))
        a += (2.0 * M_PI);
    if (a >= M_PI)
        a -= (2.0 * M_PI);
    return a;
};

/**
 * Normalize the angle to \f$(-180, 180)\f$ degree unit
 * \param a input angle value
 * \return normalized angle
 */
template<typename T>
T inline norm_a_deg(T a) {
    return RAD2DEG(norm_a_rad(LB_DEG2RAD(a)));
}

/**
 * Find the minimum different between two input angle in radian unit
 * \param a input angle value
 * \param b input angle value
 * \return minimum different angle (b-a)
 */
template<typename T>
T inline min_angle_diff(T a, T b) {
    a = norm_a_rad(a);
    b = norm_a_rad(b);

    T d_angle = b - a;

    if(fabs(d_angle) > M_PI) {
        //wrong direction
        if(d_angle >= 0) {
            d_angle = -((2*M_PI) - d_angle);
        } else {
            d_angle = ((2*M_PI) + d_angle);
        }
    }
    return d_angle;
}

/**
 * Compute a cumulative summation.
 * @param v number vector
 * @param sum output vector
 */
template<typename T>
void inline cum_sum(const std::vector<T>& v, std::vector<T>& sum) {
    if(v.size() == 0) return;
    if(sum.size() != v.size()) sum.resize(v.size());
    sum[0] = v[0];
    for(size_t i = 1; i < v.size(); i++) {
        sum[i] = sum[i-1] + v[i];
    }
}

/**
 * Compute a square summation
 * @param v input
 * @return square sum of all value in v
 */
template<typename T>
T inline square_sum(const std::vector<T>& v) {
    T sum = 0;
    for(size_t i = 0; i < v.size(); i++) {
        sum += LB_SQR(v[i]);
    }
    return sum;
}

/* @} */



/** \defgroup g_lib_marco Helper macros for the library */
/* @{ */
//simple print function
#define PRINTVAR(x)         (std::cerr << #x << ":" << (x) << "\n")
#define PRINTVALUE(x)       (std::cerr << (x) << "\n")
#define PRINTVEC(x) \
    for(size_t idx = 0; idx < x.size(); idx++) { \
        std::cerr << idx << "," << x[idx] << "\n"; \
    }

//open file
#define open_file_with_exception(f, n) \
    f.open(n.c_str()); \
    if(!f.is_open()) { \
        throw LibRoboticsIOException("Cannot open: %s", n.c_str()); \
    }

//load configuration from text file
#define load_cfg_from_text_file(x, f)   \
    f >> x; \
    PRINTVAR(x); \
    getline(f,tmp);


//check vector size
#define check_vsize2(v0, v1)                  (v0.size() == v1.size())
#define check_vsize3(v0, v1, v2)              (check_vsize2(v0,v1) && check_vsize2(v0,v2))
#define check_vsize4(v0, v1, v2, v3)          (check_vsize3(v0, v1, v2) && check_vsize2(v0, v3))
#define check_vsize5(v0, v1, v2, v3, v4)      (check_vsize4(v0, v1, v2, v3) && check_vsize2(v0, v4))

//warn on vector size compare
#define warn_vsize2(v0, v1) \
    if(!check_vsize2(v0,v1)) { \
        warn("#v0 and #v1 size are not match");\
    }
/* @} */


/**
 * Main namespace for The C++ Robotics Library
 */
namespace librobotics {

    struct LibRoboticsException;

#ifdef librobotics_use_vt100
    const char t_normal[] = { 0x1b,'[','0',';','0',';','0','m','\0' };
    const char t_red[]    = { 0x1b,'[','4',';','3','1',';','5','9','m','\0' };
    const char t_bold[]   = { 0x1b,'[','1','m','\0' };
    const char t_purple[] = { 0x1b,'[','0',';','3','5',';','5','9','m','\0' };
    const char t_green[]  = { 0x1b,'[','0',';','3','2',';','5','9','m','\0' };
#else
    const char t_normal[] = { '\0' };
    const char *const t_red = librobotics::t_normal,
               *const t_bold = librobotics::t_normal,
               *const t_purple = librobotics::t_normal,
               *const t_green = librobotics::t_normal;
#endif

    void inline info() { fprintf(stderr, "LibRobotics V 0.1\n"); }

    /**
     * Get/set the current LibRobotics exception mode.
     * The way error messages are handled by LibRobotics can be changed dynamically, using this function.
     * Possible values are :
     *      - 0 to hide debug messages (quiet mode, but exceptions are still thrown).
     *      - 1 to display debug messages on standard error (stderr).
     *      - 2 to display debug messages in modal windows (default behavior).
     */
    inline unsigned int& exception_mode() { static unsigned int mode = librobotics_debug; return mode; }


    /*
     * Definition of the LibRobotics: Exception structures
     */
    struct LibRoboticsException {
    #define _librobotics_exception_err(etype, disp_flag) \
        std::va_list ap; va_start(ap,format); std::vsprintf(message,format,ap); va_end(ap); \
        switch (librobotics::exception_mode()) { \
            case 0: break; \
            case 1: \
            case 2: \
                std::fprintf(stderr,"\n%s# %s%s : %s\n\n",librobotics::t_red,etype,librobotics::t_normal,message); \
                break; \
            default: std::fprintf(stderr,"\n%s# %s%s : %s\n\n",librobotics::t_red,etype,librobotics::t_normal,message); \
        } \
        if (librobotics::exception_mode()>=2) librobotics::info();

        char message[1024]; //!< Message associated with the error that thrown the exception.
        LibRoboticsException() {
            message[0] = '\0';
        }
        LibRoboticsException(const char *format, ...) {
            _librobotics_exception_err("LibRoboticsException",true);
        }
    };

    // The LibRoboticsInstanceException class is used to throw an exception related
    // to a non suitable instance encountered in a library function call.
    struct LibRoboticsInstanceException: public LibRoboticsException {
        LibRoboticsInstanceException(const char *format, ...) { _librobotics_exception_err("LibRoboticsInstanceException",true); }
    };

    // The LibRoboticsArgumentException class is used to throw an exception related
    // to invalid arguments encountered in a library function call.
    struct LibRoboticsArgumentException: public LibRoboticsException {
        LibRoboticsArgumentException(const char *format, ...) { _librobotics_exception_err("LibRoboticsArgumentException",true); }
    };

    // The LibRoboticsIOException class is used to throw an exception related
    // to Input/Output file problems encountered in a library function call.
    struct LibRoboticsIOException: public LibRoboticsException {
        LibRoboticsIOException(const char *format, ...) { _librobotics_exception_err("LibRoboticsIOException",true); }
    };

    // The LibRoboticsWarningException class is used to throw an exception for warnings
    // encountered in a library function call.
    struct LibRoboticsWarningException: public LibRoboticsException {
        LibRoboticsWarningException(const char *format, ...) { _librobotics_exception_err("LibRoboticsWarningException",false); }
    };

    // The LibRoboticsRuntimeException class is used to throw an exception for warnings
    // encountered in a library function call.
    struct LibRoboticsRuntimeException: public LibRoboticsException {
        LibRoboticsRuntimeException(const char *format, ...) { _librobotics_exception_err("LibRoboticsRuntimeException",false); }
    };

    /**
     * Display a warning message.
     * \param format is a C-string describing the format of the message, as in <tt>std::printf()</tt>.
     */
    inline void warn(const char *format, ...) {
        if (librobotics::exception_mode() >= 1) {
            char message[8192];
            std::va_list ap;
            va_start(ap,format);
            std::vsprintf(message,format,ap);
            va_end(ap);
            #ifdef librobotics_strict_warnings
                throw LibRoboticsWarningException(message);
            #else
                std::fprintf(stderr,"%s# LibRobotics Warning%s : %s\n",librobotics::t_red,librobotics::t_normal,message);
            #endif
        }
    }

    /*----------------------------------------------
     *
     * Definition of the LibRobotics: Utilities functions
     *
     ----------------------------------------------*/

    /**
     * Get current time of day
     * \return time in millisecond
     */
    inline unsigned long utils_get_current_time() {
#if librobotics_OS == 1
      struct timeval st_time;
      gettimeofday(&st_time,0);
      return (unsigned long)(st_time.tv_usec/1000 + st_time.tv_sec*1000);
#elif librobotics_OS == 2
      static SYSTEMTIME st_time;
      GetSystemTime(&st_time);
      return (unsigned long)(st_time.wMilliseconds + 1000*(st_time.wSecond + 60*(st_time.wMinute + 60*st_time.wHour)));
#else
      return 0;
#endif
    }

    /*-------------------------------------------------------------------------
     *
     * Definition of the LibRobotics: Statistic Functions
     *
     -------------------------------------------------------------------------*/
    /**
     * Probability density function (PDF) of the normal distribution.
     * @param v variance
     * @param m mean
     * @param x
     * @return PDF(x)
     */
    inline double stat_pdf_normal_dist(double v, double m, double x) {
        if(v <= 0) return 0;
        return (1.0/sqrt(2*M_PI*v)) * exp(-LB_SQR(x - m) / (2.0 * v));
    }

    /**
     * Probability density function (PDF) of the triangular distribution.
     * @param v
     * @param m
     * @param x
     * @return PDF(x)
     */
    inline double stat_pdf_normal_triangular_dist(double v, double m, double x) {
        //SQRT6 = 2.449489743
        if(v <= 0) return 0;
        double p = (1.0/(2.449489743 * sqrt(v))) - (fabs(x - m)/(6.0 * v));
        return LB_MAX(0.0, p);
    }

    /**
     * PDF of the exponential distribution.
     * @param rate
     * @param x
     * @return PDF(x)
     */
    inline double stat_pdf_exponential_dist(double rate, double x) {
        if(x < 0) return 0;
        return rate * exp(-rate * x);
    }

    /**
     * Use a specific srand initialization to avoid multi-threading problems
     * (executed only one time for a single program).
     */
    inline void  stat_srand() {
        static bool first_run = true;
        if(first_run) {
            std::srand(utils_get_current_time());
            unsigned char *const rand_mem = new unsigned char[1+std::rand()%2048];
            std::srand((unsigned int)(std::rand() + (unsigned long)rand_mem));
            delete[] rand_mem;
            first_run = false;
        }
    }

    /**
     * Return a random variable between \f$[0,1]\f$ with respect to an uniform distribution.
     */
    inline double stat_rand() {
        return (double)std::rand()/RAND_MAX;
    }

    /**
     * Return a random variable between \f$[-1,1]\f$ with respect to an uniform distribution.
     */
    inline double stat_crand() {
        return 1.0 - (2.0 * stat_rand());
    }

    /**
     * Sample a random value from (approximate) normal distribution with zero mean.
     * @param v variance
     * @return random sample from normal distribution with zero mean
     */
    inline double stat_sample_normal_dist(double v) {
        stat_srand();
        double sum = 0;
        for(int i = 0; i < 12; i++) {
            sum += (stat_crand() * v);
        }
        return sum/2.0;
    }

    /**
     * Sample a random value from (approximate) triangular distribution with zero mean.
     * @param v variance
     * @return random sample from triangular distribution with zero mean
     */
    inline double stat_sample_triangular_dist(double v) {
        //SQRT(6) / 2 = 1.224744871
        stat_srand();
        return 1.224744871 * ((stat_crand()*v) +  (stat_crand()*v));
    }

    /**
     * Sample a random value from uniform distribution in a circle.
     * (http://www.comnets.uni-bremen.de/itg/itgfg521/per_eval/p001.html)
     * @param a angle result \f$[-\pi, \pi]\f$
     * @param r radius result \f$[-1, 1]\f$
     */
    inline void stat_sample_circle_uniform_dist(double& a, double& r) {
        stat_srand();
        a = stat_crand() * M_PI;
        r = sqrt(stat_rand());
    }

    template<typename T>
    void stat_stratified_random(std::vector<T>& v, int n) {
        double k = 1.0/n;
        double k_2 = k * 0.5;
        if((int)v.size() != n) v.resize(n);
        for(int i = 0; i < n; i++) {
            v[i] = (k_2 + (k*i)) + (stat_rand() * k) - k_2;
        }
    }




    /*--------------------------------------------------------------------------------
     *
     * Definition of the LibRobotics: 2D robot configuration structures and functions
     *
     --------------------------------------------------------------------------------*/
    /**
     * Template class for 2D vector
     */
    template<typename T> struct vec2 {
        T x, y;

        ///Constructor
        vec2() : x(0), y(0) { }

        ///Constructor
        template<typename T1>
        vec2(T1 xx, T1 yy) : x(xx), y(yy) { }

        ///Copy constructor
        template<typename T1>
        vec2(const vec2<T1>& v) : x((T)v.x), y((T)v.y) { }

        ///Unary minus
        vec2 operator - ( ) const { return vec2(-x, -y); }

        ///Addition for vector/vector
        template<typename T1>
        vec2 operator + (const vec2<T1>& v) const { return vec2(x + (T)v.x, y + (T)v.y); }

        ///Subtraction for vector/vector
        template<typename T1>
        vec2 operator - (const vec2<T1>& v) const { return vec2(x - (T)v.x, y - (T)v.y); }

        ///Basic assignment for vector/vector
        template<typename T1>
        vec2& operator = (const vec2<T1>& v) {
            x = v.x;
            y = v.y;
            return *this;
        }

        ///Assignment by addition for vector/vector
        template<typename T1>
        vec2& operator += (const vec2<T1>& v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        ///Assignment by subtraction for vector/vector
        template<typename T1>
        vec2& operator -= (const vec2<T1>& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        ///Dot product between two vectors
        template<typename T1>
        T operator ^ (const vec2<T1>& v) const {
            return (T)((x*v.x) + (y*v.y));
        }

        ///Cross product between two vectors
        template<typename T1>
        T operator * (const vec2<T1>& v) const {
            return (T)((x*v.y) - (y*v.x));
        }

        ///Multiply by scalar value
        template<typename T1>
        vec2<T1> operator * (const T1& s) const {
            return vec2<T1>(x*s, y*s);
        }

        ///Divide by scalar value
        template<typename T1>
        vec2<T1> operator / (const T1& s) const {
            return vec2<T1>(x/s, y/s);
        }

        ///Assignment by multiply with scalar value
        template<typename T1>
        vec2& operator *= (const T1& s) {
            x *= s;
            y *= s;
            return (*this);
        }

        ///Assignment by divide with scalar value
        template<typename T1>
        vec2& operator /= (const T1& s) {
            x /= s;
            y /= s;
            return (*this);
        }

        ///Get size
        T size( ) const {
            return (T)sqrt(x*x + y*y);
        }

        ///Get square size
        T sqrSize( ) const {
            return (T)(x*x + y*y);
        }

        ///Get angle in \f$(-\pi, \pi)\f$ radian range
        T theta() const {
            return (T)atan2(y,x);
        }

        ///Get angle in \f$(0, 2\pi)\f$ radian range
        T theta_2PI() const {
            T tmp = atan2(y,x);
            if(tmp < 0) tmp += 2 * M_PI;
            return tmp;
        }

        ///Get angle in \f$(-180, 180)\f$ degree range
        T degree() const {
            return (T)RAD2DEG(atan2(y,x));
        }

        ///Get angle in \f$(0, 360)\f$ degree range
        T degree_360() const {
            return (T)RAD2DEG(theta_2PI());
        }

        ///Check for zero size vector
        bool is_zero() const {
            return (this->size() <= LB_IS_ZERO);
        }

        ///Get normalized vector
        vec2 norm() const {
            if (is_zero()) {
                return vec2();
            } else {
                return vec2((*this)/size());
            }
        }

        ///Normalize the vector
        vec2& normalize() {
            if (is_zero()) {
                x = 0;
                y = 0;
                return *this;
            } else {
                return (*this)/size();
            }
        }

        /**
         * Get rotated vector
         * \param angle rotate angle
         * \param angle unit select (true for radian, false for degree)
         */
        template<typename T1>
        vec2 rot(T1 angle, bool rad = true) const {
            if(!rad) angle = LB_DEG2RAD(angle);
            T1 c = cos(angle);
            T1 s = sin(angle);
            return vec2((T)(x*c - y*s), (T)(x*s + y*c));
        }

        /**
         * Rotate the vector
         * \param angle rotate angle
         * \param angle unit select (true for radian, false for degree)
         */
        template<typename T1>
        vec2& rotate(T1 angle, bool rad = true) {
            vec2<T> tmp = this->rot(angle, rad);
            x = tmp.x;
            y = tmp.y;
            return *this;
        }

        ///Print vector component to stand output
        void print() {
            std::cout << *this << std::endl;
        }

        ///Support for output stream operator
        friend std::ostream& operator << (std::ostream& os, const vec2<T>& v) {
            return os << v.x << " " << v.y;
        }

        ///Support for input stream operator
        friend std::istream& operator >> (std::istream& is, vec2<T>& v) {
            is >> v.x >> v.y;
            return is;
        }
    };

    /**
     * vec2 with int data type (Some operator for function will not work correctly)
     */
    typedef vec2<int> vec2i;

    /**
     * vec2 with long data type (Some operator for function will not work correctly)
     */
    typedef vec2<long> vec2l;

    /**
     * vec2 with float data type
     */
    typedef vec2<float> vec2f;

    /**
     * vec2 with double data type
     */
    typedef vec2<double> vec2d;

    /**
     * Template class for 2D robot position configuration.
     */
    template<typename T> struct pose2 {
        T x;    //!< X position
        T y;    //!< Y position
        T a;    //!< Heading direction

        ///Constructor
        pose2() : x(0), y(0), a(0)
        { }

        ///Constructor
        template<typename T1>
        pose2(T1 xx, T1 yy, T1 aa) :
            x(xx), y(yy), a(aa)
        { }

        ///Constructor
        template<typename T1>
        pose2(vec2<T1> p, T1 aa) :
            x(p.x), y(p.y), a(aa)
        { }

        ///Copy constructor
        template<typename T1>
        pose2(const pose2<T1>& p2) :
            x(p2.x), y(p2.y), a(p2.a)
        { }


        ///Addition
        template<typename T1>
        pose2 operator + (const pose2<T1>& pose) const {
            return pose2(pose.x + x, pose.y + y, norm_a_rad(pose.a + a));
        }

        ///Subtraction
        template<typename T1>
        pose2 operator - (const pose2<T1>& pose) const {
            return pose2(x - pose.x, y - pose.y, norm_a_rad(a - pose.a));
        }

        template<typename T1>
        pose2 operator * (T1 val) const {
            return pose2(x * val, y * val , a);
        }

        vec2<T> vec() const {
            return vec2<T>(x, y);
        }

        template<typename T1>
        vec2<T> vec_to(const pose2<T1>& pose) const {
            return vec2<T>(pose.x - x, pose.y - y);
        }

        template<typename T1>
        T dist_to(const pose2<T1>& pose) {
            return sqrt(LB_SQR(pose.x - x) + LB_SQR(pose.y - y));
        }

        template<typename T1>
        T angle_to(const pose2<T1>& pose) {
            return norm_a_rad(pose.a - a);
        }

        void print() {
            std::cout << *this << std::endl;
        }

        /// support for output stream
        friend std::ostream& operator << (std::ostream& os, const pose2<T>& p2) {
            return os << p2.x << " " << p2.y << " " << p2.a;
        }

        /// support for input stream
        friend std::istream& operator >> (std::istream& is, pose2<T>& p2) {
            is >> p2.x >> p2.y >> p2.a;
            return is;
        }

    };
    typedef pose2<float> pose2f;
    typedef pose2<double> pose2d;

    template<typename T> struct bbox2 {
        vec2<T> min, max;
    };
    typedef bbox2<int> bbox2i;
    typedef bbox2<long> bbox2l;
    typedef bbox2<float> bbox2f;
    typedef bbox2<double> bbox2d;

    /*-------------------------------------------------------------------------
     *
     * Definition of the LibRobotics: 2D vector and pose function
     *
     -------------------------------------------------------------------------*/

    template<typename T> bool compare_vec2_angle( const vec2<T>& i, const vec2<T>& j)
    {
        double thetai = atan2(i.y, i.x);
        if(thetai < 0) thetai += (2*M_PI);
        double thetaj = atan2(j.y, j.x);
        if(thetaj < 0) thetaj += (2*M_PI);
        return thetai < thetaj;
    }

    /*-------------------------------------------------------------------------
     *
     * Definition of the LibRobotics: 2D map information
     *
     -------------------------------------------------------------------------*/
    template<typename T> struct map_feature2 {


    };

    /**
     * Template class for 2D grid map.
     */
    template<typename T> struct map_grid2 {
        vec2i mapsize;      //!< Size of the map
        pose2<T> offset;    //!< Map offset in real world unit (m, mm, cm...)
        vec2<T> center;     //!< Map center in real world unit (m, mm, cm...)
        T resolution;       //!< Map resolution real world unit/map size unit
        T angle_res;
        int angle_step;
        std::vector<std::vector<T> > mapprob; //!< Value of each grid cell
        std::vector<std::vector<std::vector<T> > > ray_casting_cache;

        ///Constructor
        map_grid2() : resolution(1)
        { }

        ///Print out map information to standard output
        void print_info() {
            PRINTVAR(mapsize);
            PRINTVAR(offset);
            PRINTVAR(center);
            PRINTVAR(resolution);
        }

        /**
         * Directly check grid position with map size.
         * @param x grid coordinate
         * @param y grid coordinate
         * @return true if (x,y) is inside the map
         */
        bool inline is_inside(int x, int y) {
            return (x >= 0) && (x < mapsize.x) && (y >= 0) && (y < mapsize.y);
        }

        bool get_random_pts(vec2<T>& pts, T max_mapprob = 0.0, int retry = 100) {
            int x, y;
            bool pass = false;
            do {
                x = (int)(stat_rand() * mapsize.x);
                y = (int)(stat_rand() * mapsize.y);
                pass = get_real_pts(x, y, pts);
                if(pass) {
                    if(mapprob[x][y] > max_mapprob) {
                        pass = false;
                    }
                }
            } while(!pass && (retry-- > 0));
            return pass;
        }

        /**
         * Get real world unit position of given grid coordinate.
         * @param x grid coordinate
         * @param y grid coordinate
         * @param pts result in real world unit
         * @return true if (x,y) is inside the map
         */
        bool get_real_pts(int x, int y, vec2<T>& pts) {
            if(is_inside(x, y)) {
                pts.x = ((x - center.x) * resolution) + offset.x;
                pts.y = ((y - center.y) * resolution) + offset.y;
                return true;
            } else {
                return false;
            }
        }

        /**
         * Get grid coordinate from real world unit position.
         * @param x position
         * @param y position
         * @param v result in grid coordinate
         * @return true if (x,y) is inside the map
         */
        bool get_grid_coordinate(T x, T y, vec2i& v) {
            v.x = (int)(center.x + (int)LB_ROUND((x-offset.x)/resolution));
            v.y = (int)(center.y + (int)LB_ROUND((y-offset.y)/resolution));
            if(is_inside(v.x, v.y))
                return true;
            else {
//                warn("(%f, %f) is outside map", x, y);
                return false;
            }
        }

        /**
         * Get probabilistic value of give real world unit position.
         * @param x position in real world
         * @param y position in real world
         * @return value of grid (>=0) if (x,y) is inside the map
         */
        T get_grid_value(T x, T y) {
            int gx = (int)(center.x + (int)ROUND((x-offset.x)/resolution));
            int gy = (int)(center.y + (int)ROUND((y-offset.y)/resolution));
            if(is_inside(gx, gy))
                return mapprob[gx][gy];
            else
                return -1;
        }

        /**
         * Set grid at real world position with specific value.
         * @param x position in real world
         * @param y position in real world
         * @param value
         * @return true if (x,y) is inside the map
         */
        bool set_grid_value(T x, T y, T value) {
            int gx = (int)(center.x + (int)round((x-offset.x)/resolution));
            int gy = (int)(center.y + (int)round((y-offset.y)/resolution));
            if(is_inside(gx, gy)) {
                mapprob[gx][gy] = value;
                return true;
            } else
                return false;
        }

        /**
         * Compute hit point on grid coordinate from the (x,y) grid position from given direction.
         * Adapt from http://student.kuleuven.be/~m0216922/CG/raycasting.html
         * @param x grid position
         * @param y grid position
         * @param dir ray casting direction
         * @param hit_grid result of the function
         * @return -1 if (x,y) not in the map \n
         *          0 if (x,y) inside occupied \n
         *          1 if hit \n
         *          2 if not hit
         */
        int get_ray_casting_hit_point(int x, int y, T dir, vec2i& hit_grid) {
            //outside the map
            if(!is_inside(x, y))
                return -1;

            //hit itself
            if(mapprob[x][y] != 0) {
                hit_grid = vec2i(x,y);
                return 0;
            }

            int mapX = x;
            int mapY = y;
            double posX = mapX;
            double posY = mapY;
            double rayPosX = posX;
            double rayPosY = posY;
            double rayDirX = cos(dir);
            double rayDirY = sin(dir);
            double deltaDistX = sqrt(1 + LB_SQR(rayDirY) / LB_SQR(rayDirX));
            double deltaDistY = sqrt(1 + LB_SQR(rayDirX) / LB_SQR(rayDirY));

            //length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;

            //what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            int hit = 0; //was there a wall hit?
            int side; //was a NS or a EW wall hit?

            //calculate step and initial sideDist
            if (rayDirX < 0) {
                stepX = -1;
                sideDistX = (rayPosX - mapX) * deltaDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
            }
            if (rayDirY < 0) {
                stepY = -1;
                sideDistY = (rayPosY - mapY) * deltaDistY;
            } else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
            }
            //perform DDA
            while (hit == 0) {
                //jump to next map square, OR in x-direction, OR in y-direction
                if (sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                } else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }

                //Check if ray is out side map boundary
                if(!is_inside(mapX, mapY)) return 2; //dose not hit any cell

                //Check if ray has hit
                if (mapprob[mapX][mapY]> 0) hit = 1;
            }

            //hit
            hit_grid.x = mapX;
            hit_grid.y = mapY;
            return 1;
        }

        /**
         * Pre-compute ray casting result of all unoccupied gird.
         * @param angle_res ray casting angle resolution in radian
         */
        void compute_ray_casting_cache(T _angle_res) {
            if(_angle_res <= 0) {
                throw LibRoboticsRuntimeException("angle resolution must > 0");
            }
            angle_res = _angle_res;
            angle_step = (int)((2*M_PI) / angle_res + 1);
            int result;
            vec2i hit;
            int cnt = 0;
            std::cerr << "Start ray casting compute...";
            ray_casting_cache.resize(mapsize.x);
            for(int x = 0; x < mapsize.x; x++) {
                ray_casting_cache[x].resize(mapsize.y);
                if((x % 10) == 0) {
                    std::cerr << ".";
                }
                for(int y = 0; y < mapsize.y; y++) {
                    if(mapprob[x][y] > 0) {
                        //occupied grid
                        continue;
                    }
                    ray_casting_cache[x][y].resize(angle_step);
                    for(int i = 0; i < angle_step; i++) {
                        result = get_ray_casting_hit_point(x, y, i * angle_res, hit);
                        if(result == 1) {
                            ray_casting_cache[x][y][i] = LB_SIZE(x-hit.x, y-hit.y) * resolution;
                        } else {
                            ray_casting_cache[x][y][i] = -1;    //no measurement on that direction
                        }
                        cnt++;
                    }
                }
            }
            std::cerr << "done! with " << cnt << " ray casting operations\n";
        }

        /**
         * Load map data from text file.
         * Example of map with 3x3 size (do not put \\\\ comment inside the file) \n
         *      3 3             \\\\size \n
         *      0.0 0.0 0.0     \\\\offset \n
         *      0.0 0.0         \\\\center \n
         *      1.0             \\\\scale \n
         *      0.1 0.2 0.3     \\\\grid value of (x, 0) \n
         *      0.4 0.5 0.6     \\\\grid value of (x, 1) \n
         *      0.7 0.8 0.8     \\\\grid value of (x, 2) \n
         * @param filename of the map data
         */
        void load_txt(const std::string& filename) {
            std::ifstream file;
            open_file_with_exception(file, filename);
            file >> mapsize;
            file >> offset;
            file >> center;
            file >> resolution;
            if(resolution <= 0) {
                warn("resolution must > 0 -> automatic set to 1.0");
                resolution = 1.0;
            }
            center /= resolution;
            mapprob.resize(mapsize.x);
            for(int i = 0; i < mapsize.x && !file.eof(); i++) {
                mapprob[i].resize(mapsize.y);
                for(int j = 0; j < mapsize.y && !file.eof(); j++) {
                    file >> mapprob[i][j];
                }
            }
        }

        /**
         * Save map data to text file.
         * @param filename of the output map
         */
        void save_txt(const std::string& filename) {
            std::ofstream file;
            open_file_with_exception(file, filename);
            file << mapsize << "\n";
            file << offset << "\n";
            file << (center*resolution) << "\n";
            file << resolution << "\n";
            for(int i = 0; i < mapsize.x && !file.eof(); i++) {
                for(int j = 0; j < mapsize.y && !file.eof(); j++) {
                    file << mapprob[i][j] << " ";
                }
                file << "\n";
            }
            file.close();
        }



#ifdef librobotics_use_cimg
        /**
         * Load map data from image file. Image data should save in 8 bit color depth format.
         * This function will use only first channel as map data.
         * Map data will read directly for each pixel position to grid position.
         * @param filename of the map image
         * @param _offset map offset in real world unit (m, mm, cm...)
         * @param _center map center in real world unit (m, mm, cm...)
         * @param _resolution map resolution in real world unit (m, mm, cm...)
         */
        void load_image(const std::string& filename,
                        const pose2<T>& _offset,
                        const vec2<T>& _center,
                        T _resolution)
        {
            using namespace cimg_library;
            CImg<unsigned char> img;
            try {
                img.load(filename.c_str());
            } catch (CImgException& e) {
                throw LibRoboticsIOException(e.message);
            }


            mapsize.x = img.dimx();
            mapsize.y = img.dimy();
            offset = offset;
            center = _center;
            resolution = _resolution;
            if(resolution <= 0) {
                warn("resolution must > 0 -> automatic set to 1.0");
                resolution = 1.0;
            }
            center /= resolution;
            mapprob.resize(mapsize.x);
            for(int i = 0; i < mapsize.x; i++) {
                mapprob[i].resize(mapsize.y);
                for(int j = 0; j < mapsize.y; j++) {
                    mapprob[i][j] = (255 - img(i, j, 0)) / 255.0;
                    if(mapprob[i][j] < 0.5) mapprob[i][j] = 0.0;
                }
            }

            std::cout << "======= Map Setting =======\n";
            PRINTVAR(filename);
            PRINTVAR(mapsize);
            PRINTVAR(offset);
            PRINTVAR(center);
            PRINTVAR(resolution);
            std::cout << "===========================\n";

        }

        /**
         * Get image of the map
         * @param flip_x true to flip result image along X-axis
         * @param flip_y true to flip result image along Y-axis
         * @return image in CImg<unsigned char> format.
         */
        cimg_library::CImg<unsigned char>
        get_image(bool flip_x = false, bool flip_y = true) {
            using namespace cimg_library;
            CImg<unsigned char> img(mapsize.x, mapsize.y, 1, 3, 0);
            unsigned char v = 0;
            int x, y;
            for(int i = 0; i < mapsize.x; i++) {
                for(int j = 0; j < mapsize.y; j++) {
                    v = (unsigned char)(255 - (mapprob[i][j] * 255));
                    x = i;
                    y = j;

                    if(flip_x) x = (mapsize.x - 1) - x;
                    if(flip_y) y = (mapsize.y - 1) - y;

                    img(x, y, 0) = v;
                    img(x, y, 1) = v;
                    img(x, y, 2) = v;
                }
            }
            return img;
        }

#endif
    };

    typedef map_grid2<float> map_grid2f;
    typedef map_grid2<double> map_grid2d;



    /*-------------------------------------------------------------------------
     *
     * Definition of the LibRobotics: 3D robot configuration structures and functions
     *
     -------------------------------------------------------------------------*/

    template<typename T> struct vec3 {
        T x, y, z;
        vec3() : x(0), y(0), z(0) { }
    };
    typedef vec3<int> vec3i;
    typedef vec3<long> vec3l;
    typedef vec3<float> vec3f;
    typedef vec3<double> vec3d;

    template<typename T> struct pose3 {
        T x, y, z, ax, ay, az;
        pose3() : x(0), y(0), z(0), ax(0), ay(0), az(0) { }
    };
    typedef pose3<float> pose3f;
    typedef pose3<double> pose3d;

    template<typename T> struct bbox3 {
        vec3<T> min, max;
    };
    typedef bbox3<int> bbox3i;
    typedef bbox3<long> bbox3l;
    typedef bbox3<float> bbox3f;
    typedef bbox3<double> bbox3d;




    /*-------------------------------------------------------
     *
     * Definition of the LibRobotics: Log files reader (CARMEN and other simple formats)
     * (http://carmen.sourceforge.net)
     *
     -------------------------------------------------------*/

    template<typename T> struct logdata_simple_lrf {
        std::vector<std::vector<T> > lrf;
        int step;
        std::ifstream log_file;
        std::string label_lrf;
        std::string fn;

        logdata_simple_lrf() : step(0) { }
        void open(const std::string& filename,
                  const std::string& lrf_label)
        {
            open_file_with_exception(log_file, filename);
            label_lrf = lrf_label;
            fn = filename;
        }

        int read_all() {
            while(read_one_line()) {step++;}
            return step;
        }

        bool read_one_line() {
            //get label
            std::string tmp;
            log_file >> tmp;

            if(log_file.eof()) {
                warn("End of %s", fn.c_str());
                return false;
            }

            if(tmp.compare(label_lrf) == 0) {
                int max;
                log_file >> max;
                std::vector<T> ranges(max);
                for (int i = 0; i < max; i++) {
                    log_file >> ranges[i];
                }
                lrf.push_back(ranges);
            } else {
                throw LibRoboticsRuntimeException("Uninterpretable line with label: %s in %s", tmp.c_str(), fn.c_str());
            }
            return true;
        }
    };


    template<typename T1, typename T2> struct logdata_simple_odo_lrf {
        std::vector<pose2<T1> > odo;
        std::vector<std::vector<T2> > lrf;
        int step;
        std::ifstream log_file;
        std::string label_odo;
        std::string label_lrf;
        std::string fn;

        logdata_simple_odo_lrf() : step(0) { }

        void open(const std::string& filename,
                  const std::string& odo_label,
                  const std::string& lrf_label)
        {
            open_file_with_exception(log_file, filename);
            label_odo = odo_label;
            label_lrf = lrf_label;
            fn = filename;
        }

        int read_all() {
            std::cerr << "Read all log data...";
            int cnt = 0;
            while(read_one_step()) {
                cnt++;
                if(cnt % 10 == 0)
                    std::cerr << ".";
            }
            std::cerr << "done with " << step << " steps read\n";
            return step;
        }

        bool read_one_step() {
            //read 2 line (odo and lrf)
            if(!read_one_line() || !read_one_line()) {
                return false;
            }
            step++;
            return true;
        }

        bool read_one_line() {
            //get label
            std::string tmp;
            log_file >> tmp;

            if(log_file.eof()) {
                warn("End of %s", fn.c_str());
                return false;
            }

            if(tmp.compare(label_odo) == 0) {
                pose2<T1> p;
                log_file >> p;
                p.a = norm_a_rad(p.a);
                odo.push_back(p);
            } else
            if(tmp.compare(label_lrf) == 0) {
                int max;
                log_file >> max;
                std::vector<T2> ranges(max);
                for (int i = 0; i < max; i++) {
                    log_file >> ranges[i];
                }
                lrf.push_back(ranges);
            } else {
                throw LibRoboticsRuntimeException("Uninterpretable line with label: %s in %s", tmp.c_str(), fn.c_str());
            }
            return true;
        }
    };

    template<typename T1, typename T2> struct logdata_simple_odo_us {
        std::vector<pose2<T1> > odo;
        std::vector<std::vector<vec2<T2> > > us;
        int step;
        std::ifstream log_file;
        std::string label_odo;
        std::string label_us;
        std::string fn;

        logdata_simple_odo_us() : step(0) { }

        void open(const std::string& filename,
                  const std::string& odo_label,
                  const std::string& us_label)
        {
            open_file_with_exception(log_file, filename);
            label_odo = odo_label;
            label_us = us_label;
            fn = filename;
        }

        int read_all() {
            std::cerr << "Read all log data...";
            int cnt = 0;
            while(read_one_step()) {
                cnt++;
                if(cnt % 10 == 0)
                    std::cerr << ".";
            }
            std::cerr << "done with " << step << " steps read\n";
            return step;
        }

        bool read_one_step() {
            //read 2 line (odo and lrf)
            if(!read_one_line() || !read_one_line()) {
                return false;
            }
            step++;
            return true;
        }

        bool read_one_line() {
            //get label
            std::string tmp;
            log_file >> tmp;

            if(log_file.eof()) {
                warn("End of %s", fn.c_str());
                return false;
            }

            if(tmp.compare(label_odo) == 0) {
                pose2<T1> p;
                log_file >> p;
                p.a = norm_a_rad(p.a);
                odo.push_back(p);
            } else
            if(tmp.compare(label_us) == 0) {
                int max;
                log_file >> max;
                std::vector<vec2<T2> > ranges(max);
                for (int i = 0; i < max; i++) {
                    log_file >> ranges[i];
                }
                us.push_back(ranges);
            } else {
                throw LibRoboticsRuntimeException("Uninterpretable line with label: %s in %s", tmp.c_str(), fn.c_str());
            }
            return true;
        }
    };

    template<typename T1, typename T2> struct logdata_simple_odo_n_lrf {
        std::vector<pose2<T1> > odo;
        std::vector<std::vector<std::vector<T2> > > n_lrf;
        int num_lrf;
        int step;
        std::ifstream log_file;
        std::string label_odo;
        std::vector<std::string> label_n_lrf;
        std::string fn;

        logdata_simple_odo_n_lrf() : step(0) { }

        void open(const std::string& filename,
                  int lrf_num,
                  const std::string& odo_label,
                  const std::vector<std::string>& lrf_labels)
        {
            open_file_with_exception(log_file, filename);
            num_lrf = lrf_num;
            label_odo = odo_label;
            label_n_lrf = lrf_labels;
            fn = filename;
            n_lrf.resize(lrf_num);
        }

        int read_all() {
            while(read_one_step()) { }
            return step;
        }

        bool read_one_step() {
            for(int i = 0; i < (1 + num_lrf); i++) {
                if(!read_one_line())
                    return false;
            }
            step++;
            return true;
        }


        bool read_one_line() {
           //get label
           std::string tmp;
           log_file >> tmp;

           if(log_file.eof()) {
               warn("End of %s", fn.c_str());
               return false;
           }

           if(tmp.compare(label_odo) == 0) {
               pose2<T1> p;
               log_file >> p;
               p.a = norm_a_rad(p.a);
               odo.push_back(p);
           } else {
               int lrf_id = -1;
               for(int i = 0; i < num_lrf; i++) {
                   //check label
                   if(tmp.compare(label_n_lrf[i]) == 0)
                       lrf_id = i;
               }

               if(lrf_id >= 0) {
                   int max;
                   log_file >> max;
                   std::vector<T2> ranges(max);

                   int i = 0;
                   for (i = 0; i < max; i++) {
                       log_file >> ranges[i];
                   }

                   n_lrf[lrf_id].push_back(ranges);
               } else {
                   throw LibRoboticsRuntimeException("Uninterpretable line with label: %s in %s", tmp.c_str(), fn.c_str());
               }
           }
           return true;
       }
    };

    template <typename T1, typename T2> struct logdata_buggy_robot {
    	struct buggy_odo {
    		T1 ds, da, a;
    	};
    	struct buggy_gps {
    		T1 x, y, a, v;
    		int step;
    	};
    	std::vector<buggy_odo>	odo;
    	std::vector<std::vector<T2> > lrf;
    	std::vector<buggy_gps> gps;
    	int step;
    	std::ifstream log_file;
    	std::string fn;
    	bool is_gps;

    	logdata_buggy_robot() : step(0), is_gps(false) { }

        void open(const std::string& filename) {
            open_file_with_exception(log_file, filename);
            fn = filename;
        }

        int read_all() {
             while(read_one_step()) { }
             return step;
        }

        bool read_one_step() {
            for(int i = 0; i < 20; i++) {
                if(!read_one_line())
                    return false;
            }
            if(!read_one_line())
                return false;
            if(!is_gps) {
                return false;
            }
            is_gps = false;
            step++;
            return true;
        }

    	bool read_one_line() {
            //get label
            std::string tmp;
            log_file >> tmp;

            if(log_file.eof()) {
            	warn("End of %s", fn.c_str());
            	return false;
            }

            if(tmp.compare("Odo") == 0) {
            	buggy_odo odo_tmp;
            	log_file >> odo_tmp.ds;
            	log_file >> odo_tmp.da;
            	log_file >> odo_tmp.a;
            	if(odo_tmp.a < 0) odo_tmp.a += 2*M_PI;
            	odo.push_back(odo_tmp);
            } else
            if(tmp.compare("Laser") == 0) {
            	int max;
				log_file >> max;
				std::vector<T2> ranges(max);
				for (int i = 0; i < max; i++) {
					log_file >> ranges[i];
				}
				lrf.push_back(ranges);
            } else
            if(tmp.compare("GPS") == 0) {
                buggy_gps gps_tmp;
				log_file >> gps_tmp.x;
				log_file >> gps_tmp.y;
				log_file >> gps_tmp.a;
				log_file >> gps_tmp.v;
				gps.push_back(gps_tmp);
				is_gps = true;
            } else {
                throw LibRoboticsRuntimeException("Uninterpretable line with label: %s in %s", tmp.c_str(), fn.c_str());
            }
            return true;
    	}
    };



    /*-------------------------------------------------------------------------
     *
     * Definition of the LibRobotics: Particle filter Functions
     *
     -------------------------------------------------------------------------*/
    template<typename T>
    int pf_max_weight_index(const std::vector<T>& p) {
        double max_w = -1;
        int index = 0;
        for(size_t i = 0; i < p.size(); i++ ) {
            if(p[i].w > max_w) {
                index = i;
                max_w = p[i].w;
            }
        }
        return index;
    }

    template<typename T>
    bool pf_weight_compare(const T& p1, const T& p2) {
       return (p1.w < p2.w);
    }

    template<typename T>
    void pf_normalize_weight(std::vector<T>& p) {
        double sum = 0;
        for(size_t i = 0; i < p.size(); i++ ) {
            sum += p[i].w;
        }
        for(size_t i = 0; i < p.size(); i++ ) {
            p[i].w /= sum;
        }
    }

    template<typename T>
    bool pf_stratified_resample(std::vector<T>& p, int n_min) {
        pf_normalize_weight(p);
        size_t n = p.size();

        if(n < 2)
            return false;

        double square_sum = 0;

        //square sum
        for(size_t i = 0; i < n; i++) {
            square_sum += LB_SQR(p[i].w);
        }

        int n_eff = (int)(1.0/square_sum);
        if(n_eff > n_min)
            return false;

        std::vector<double> cum_sum_w(n, 0.0);
        std::vector<int> keep(n, 0);
        std::vector<double> select(n, 0.0);

        //cumulative sum
        cum_sum_w[0] = p[0].w;
        for(size_t i = 1; i < n; i++) {
            cum_sum_w[i] = cum_sum_w[i-1] + p[i].w;
        }

        stat_stratified_random(select, n);
        size_t ctr = 0;
        for(size_t i = 0; i < n; i++) {
            while((ctr < n) && (select[ctr] < cum_sum_w[i])) {
                keep[ctr] = i;
                ctr++;
            }
        }

        std::vector<T> p_tmp(n);
        for(size_t i = 0; i < n; i++) {
            p_tmp[i] = p[keep[i]];
        }

        for(size_t i = 0; i < n; i++) {
            p[i] = p_tmp[i];
            p[i].w = 1.0/n;
        }
        return true;
    }


    /*--------------------------------------------------------------------------------
     *
     * Definition of the LibRobotics: 2D Laser Range Finder (LRF) data structures and functions
     *
     --------------------------------------------------------------------------------*/

    enum lrf_range_condition {
        ERR_NONE        = 0x00,
        ERR_RANGE       = 0x01,     //too far
        ERR_MOVE        = 0x02,     //moving object
        ERR_MIXED       = 0x04,     //mixed pixel
        ERR_OCCLUDED    = 0x08,     //occluded
        ERR_EMPTY       = 0x10      //no measurement
    };

    enum lrf_feature_type {
        TYPE_SEGMENT = 0,
        TYPE_LINE,
        TYPE_ARC,
        TYPE_CORNER,
        TYPE_SMALL_OBJ,
        TYPE_LEG,
        TYPE_LEG2
    };

    template<typename T1, typename T2> struct lrf_data {
        std::vector<T1> ranges;
        std::vector<T2> angles;
    };
    typedef lrf_data<int, float> lrf_data_if;
    typedef lrf_data<int, double> lrf_data_id;

    template<typename T1, typename T2>
    void lrf_init_lrf_data_angle(lrf_data<T1, T2>& lrf, T2 startTheta, T2 thetaStep) {
        if(lrf.angles.size() == 0) {
            librobotics::warn("size of angles is 0");
            return;
        }

        T2 tmpTheta;
        for(size_t i = 0; i < lrf.angles.size(); i++) {
            tmpTheta = startTheta + (i * thetaStep);
            lrf.angles[i] = tmpTheta;
        }
    }

    template<typename T>
    void lrf_init_fi_table(T startTheta,
                           T thetaStep,
                           std::vector<T>& fiTable)
    {
        T tmpTheta;
        for(size_t i = 0; i < fiTable.size(); i++) {
            tmpTheta = startTheta + (i * thetaStep);
            fiTable[i] = tmpTheta;
        }
    }

    template<typename T>
    void lrf_init_cos_sin_table(T startTheta,
                                T thetaStep,
                                std::vector<T>& cosTable,
                                std::vector<T>& sinTable)
    {
        T tmpTheta;
        for(size_t i = 0; (i < cosTable.size()) && (i < sinTable.size()); i++) {
            tmpTheta = startTheta + (i * thetaStep);
            cosTable[i] = cos(tmpTheta);
            sinTable[i] = sin(tmpTheta);
        }
    }

    template<typename T1, typename T2>
    void lrf_scan_range_from_scan_point(const std::vector<vec2<T1> >& scan_point,
                             std::vector<T2>& ranges,
                             T2 convert = 1.0)
    {
        if(ranges.size() != scan_point.size()) {
            librobotics::warn("scanPose and ranges size are not match");
        }

        for(size_t i = 0; (i < scan_point.size()) && (i < ranges.size()); i++ ) {
            ranges[i] = (T2)scan_point[i].size() * convert;
        }
    }

    template<typename T1, typename T2, typename T3>
    void lrf_scan_point_from_scan_range(const std::vector<T1>& ranges,
                                       const std::vector<T2>& cosTable,
                                       const std::vector<T2>& sinTable,
                                       std::vector<vec2<T3> >& scan_point,
                                       T3 scale = 1.0,
                                       int step = 1,
                                       bool flip = false)
    {
        size_t nPts = ranges.size();
        if((cosTable.size() != nPts) || (sinTable.size() != nPts)) {
            throw librobotics::LibRoboticsRuntimeException("cos/sin table size are not match");
        }

        if(scan_point.size() != nPts) {
            scan_point.resize(nPts);
        }

        T3 r = 0;;
        int idx = 0;
        int j = 0;
        for(size_t i = 0; i < nPts; i+=step ) {
            idx = (!flip) ? i : ((nPts - 1) - i);
            r = ranges[i] * scale;
            scan_point[j].x = r * cosTable[idx];
            scan_point[j].y = r * sinTable[idx];
            j++;
        }
    }

    template<typename T1, typename T2>
    void lrf_scan_point_to_global_pose(std::vector<vec2<T1> >& scan_point,
                                      pose2<T2> lrf_offset,
                                      pose2<T2> global_pose)
    {
        if(scan_point.size() == 0) {
            librobotics::warn("size of scan_point is 0");
            return;
        }

        for(size_t i = 0; i < scan_point.size(); i++ ) {
            scan_point[i].rotate(lrf_offset.a);
            scan_point[i] += lrf_offset.vec();
            scan_point[i].rotate(global_pose.a);
            scan_point[i] += global_pose.vec();
        }

    }

    template<typename T>
    void lrf_range_glitch_filter(std::vector<T>& ranges,
                                 T value = 0)
    {
        for(size_t i = 1; i < (ranges.size() - 1); i++ ) {
            if(ranges[i-1] != value &&
               ranges[i] == value &&
               ranges[i+1] != value)
            {
                ranges[i] = (T)((ranges[i-1] + ranges[i+1]) / 2.0);
            } else
            if(ranges[i-1] == value &&
               ranges[i] != value &&
               ranges[i+1] == value)
            {
                ranges[i] = value;
            }
        }
    }

    template<typename T>
    void lrf_range_median_filter(std::vector<T>& ranges,
                                 size_t halfWndSide = 2)
    {
        size_t nRange = ranges.size();
        if(nRange < ((halfWndSide * 2) + 1))
            return;

        std::vector<T> r((halfWndSide * 2) + 1,0);
        int k = 0, l = 0;
        for(size_t i = 0; i < nRange; i++) {
            k = 0;
            for(int j = i - halfWndSide ; j <= (int)(i + halfWndSide); j++) {
                l = (j < 0) ? 0 : j;
                l = (j >= (int)nRange) ? (nRange - 1) : l;
                r[k] = ranges[l];
                k++;
            }
            std::sort(r.begin(), r.end());
            ranges[i] = r[halfWndSide];
        }
    }

    template<typename T>
    void lrf_range_threshold(std::vector<T>& ranges,
                             T minValue,
                             T newMinValue = 0,
                             T maxValue = (T)(1e6),
                             T newMaxValue = 0)
    {
        for(size_t i = 0; i < ranges.size(); i++ ) {
            if(ranges[i] < minValue) {
                ranges[i] = newMinValue;
            }
            else
            if(ranges[i] > maxValue) {
                ranges[i] = newMaxValue;
            }
        }
    }

    template<typename T>
    void lrf_range_threshold(std::vector<T>& ranges,
                             std::vector<unsigned int>& bad,
                             T minValue,
                             T newMinValue = 0,
                             T maxValue = (T)(1e6),
                             T newMaxValue = 0)
    {
        if(bad.size() != ranges.size()) {
            throw librobotics::LibRoboticsRuntimeException("bad and ranges size are not match");
        }

        for(size_t i = 0; i < ranges.size(); i++ ) {
            if(ranges[i] <= minValue) {
                ranges[i] = newMinValue;
                bad[i] = ERR_EMPTY;
            }
            else
            if(ranges[i] >= maxValue) {
                ranges[i] = newMaxValue;
                bad[i] = ERR_RANGE;
            } else {
                bad[i] = ERR_NONE;
            }
        }
    }

    template<typename T>
    void lrf_range_check(std::vector<T>& ranges,
                         T IS_MAX_RANGE_VALUE, T MAX_RANGE_VALUE,
                         T newMaxRangeValue,
                         T BAD_RANGE,
                         T newBadRangeValue)
    {
        for(size_t i = 0; i < ranges.size(); i++ ) {
            if((ranges[i] == IS_MAX_RANGE_VALUE) || (ranges[i] > MAX_RANGE_VALUE)) {
                ranges[i] = newMaxRangeValue;
            } else {
                if(ranges[i] <= BAD_RANGE) {
                    ranges[i] = newBadRangeValue;
                }
            }
        }
    }

    template<typename T>
    void lrf_range_segment(const std::vector<T>& ranges,
                           std::vector<int>& seg,
                           T rangeThreshold,
                           T minValue = 0)
    {
        if(seg.size() != ranges.size()) {
            throw librobotics::LibRoboticsRuntimeException("seg and ranges size are not match");
        }

        bool newSegment = true;
        T lastRange = 0;
        int nSegment = 0;

        for(size_t i = 0; i < ranges.size(); i++) {
            if(ranges[i] > minValue) {
                if(newSegment) {
                  //start new segment
                  seg[i] = nSegment;
                  newSegment = false;
                } else {
                    T range_err = ranges[i] - lastRange;
                    if(fabs((double)range_err) > rangeThreshold) {
                      //end current segment
                      nSegment++;

                      //start new segment
                      seg[i] = nSegment;
                      lastRange = ranges[i];
                      newSegment = false;

                  } else {
                      //continue current segment
                      seg[i] = nSegment;
                      lastRange = ranges[i];
                  }
                }
            } else {
                if(!newSegment) {
                    //end current segment
                    nSegment++;
                    newSegment = true;
                } else {
                    //ignore all value below thresholds
                    seg[i] = -1;
                }
            }
        }
    }

    template<typename T>
    void lrf_save_to_file(const std::string& filename,
                          const std::vector<T>& lrf_range,
                          const std::string& sperator = ",")
    {
        std::ofstream file;
        open_file_with_exception(file, filename);
        for(size_t i = 0; i < lrf_range.size(); i++ ) {
            file << i << sperator << lrf_range[i] << std::endl;
        }
        file.close();
    }

    template<typename T1, typename T2>
    void lrf_save_to_file(const std::string& filename,
                          const std::vector<T1>& lrf_range0,
                          const std::vector<T2>& lrf_range1,
                          const std::string& sperator = ",")
    {
        std::ofstream file;
        open_file_with_exception(file, filename);
        warn_vsize2(lrf_range0, lrf_range1);
        for(size_t i = 0;
            (i < lrf_range0.size()) && (i < lrf_range0.size());
            i++ )
        {
            file << i << sperator << lrf_range0[i]
                      << sperator << lrf_range1[i] << std::endl;
        }
        file.close();
    }

    template<typename T1, typename T2, typename T3>
    void lrf_save_to_file(const std::string& filename,
                      const std::vector<T1>& lrf_range0,
                      const std::vector<T2>& lrf_range1,
                      const std::vector<T3>& lrf_range2,
                      const std::string& sperator = ",")
    {

    }


    template<typename T>
    void lrf_save_to_file(const std::string& filename,
                          const std::vector<std::vector<T> >& lrf_ranges_array,
                          int step = -1,
                          const std::string& sperator = ",")
    {
        std::ofstream file;
        open_file_with_exception(file, filename);



    }

    template<typename T>
    void lrf_save_to_file(const std::string& filename,
                          const std::vector<vec2<T> >& lrf_pts,
                          const std::string& sperator = ",")
    {
        std::ofstream file;
        open_file_with_exception(file, filename);
        for(size_t i = 0; i < lrf_pts.size(); i++ ) {
            file << i << sperator << lrf_pts[i].x << sperator << lrf_pts[i].y << std::endl;
        }
        file.close();
    }

    template<typename T>
    void lrf_save_to_file(const std::string& filename,
                          const std::vector<std::vector<vec2<T> > >& lrf_pts_array,
                          int step = -1,
                          const std::string& sperator = ",")
    {

    }

#ifdef librobotics_use_cimg
    template<typename T1, typename T2>
    void lrf_draw_scan_point_to_cimg(const std::vector<vec2<T1> >& scan_point,
                                     cimg_library::CImg<T2>& img,
                                     const T2 color[],
                                     bool draw_line = false,
                                     float scale = 0.1,
                                     pose2<T1> offset = pose2<T1>(),
                                     bool flip_x = false,
                                     bool flip_y = true)
    {
        using namespace cimg_library;

        int dimx = img.dimx();
        int dimy = img.dimy();
        int xoffset = dimx/2;
        int yoffset = dimy/2;

        CImgList<T1> points;
        vec2<T1> tmp;
        for(size_t  i = 0; i < scan_point.size(); i++) {
            if((offset.x == offset.y) && (offset.y == offset.a) && (offset.a == 0))
                tmp = scan_point[i];
            else
                tmp = scan_point[i].rot(offset.a) + offset.vec();
            T1 x = tmp.x;
            if(flip_x) x = -x;
            x = x * scale + xoffset;
            T1 y = tmp.y;
            if(flip_y) y = -y;
            y = y * scale + yoffset;
            points.push_back(CImg<>::vector(x, y));
        }

        if(draw_line) {
            img.draw_line(points, color);
        } else {
            img.draw_point(points, color);
        }
    }
#endif
    /*--------------------------------------------------------------------------------
     *
     * Definition of the LibRobotics: 2D Measurement and Motion Model
     *
     --------------------------------------------------------------------------------*/

    /**
     * Namespace for robot mathematics model
     */
    namespace math_model {
        /**
         * Measurement model for range sensor from CH6 of Probabilistic Robotics book.
         * http://robots.stanford.edu/probabilistic-robotics/ \n
         * @param x measurement data
         * @param x_hit expected measurement range
         * @param x_max maximum possible measurement range
         * @param var_hit variance of the measurement
         * @param rate_short rate of exponential distribution
         * @param z[4] weighted average for z_hit, z_short, z_max. z_rand and z[0]+z[1]+z[2]+z[3]=1;
         * @return
         */
        template<typename T>
        T beam_range_finder_measurement(T x,
                                        T x_hit,
                                        T x_max,
                                        T var_hit,
                                        T rate_short,
                                        T z[4])
        {
            T p_hit =   ((x > 0) && (x <= x_max)) ? stat_pdf_normal_dist(var_hit, x_hit, x) : 0.0;
            T p_short = ((x > 0) && (x <= x_hit)) ? stat_pdf_exponential_dist(rate_short, x) : 0.0;
            p_short *= 1.0 / (1.0 - exp(-rate_short * x_hit));
            T p_max =   (x <= 0 || x >= x_max ? 1.0 : 0.0);
            T p_rand =  ((x > 0) && (x < x_max)) ? 1.0/x_max : 0.0;
            return (z[0] * p_hit) + (z[1] * p_short) + (z[2] * p_max)  + (z[3] * p_rand);
        }

        /**
         * Closed form velocity motion model for compute \f$p(x_t|u_t, x_{t-1})\f$
         * @param pt    hypothesized pose \f$(x', y', \theta')^T\f$
         * @param ut    control \f$(v, w)^T\f$
         * @param p     initial pose \f$(x, y, \theta)^T\f$
         * @param dt    update time
         * @param var   robot specific motion error parameters \f$(\sigma_1 ... \sigma_6) \f$
         * @return \f$p(x_t|u_t, x_{t-1})\f$
         */
        template<typename T>
        T velocity_motion(pose2<T> pt,
                          vec2<T> ut,
                          pose2<T> p,
                          T dt,
                          T var[6])
        {
            T x_x = p.x - pt.x;
            T y_y = p.y - pt.y;
            T tmp0 = ((x_x*cos(p.a)) + (y_y*sin(p.a)));
            T tmp1 = ((y_y*cos(p.a)) - (x_x*sin(p.a)));
            T u, xx, yy, rr, aa, v, w;

            u = 0.0;
            if(tmp1 != 0) {
                u = 0.5 * (tmp0/tmp1);
            }

            //compute center and radius of the circle
            xx = ((p.x + pt.x) * 0.5) + (u*(p.y - pt.y));
            yy = ((p.y + pt.y) * 0.5) + (u*(pt.x - p.x));
            rr = sqrt(SQR(pt.x - xx) + SQR(pt.y - yy));

            aa = min_angle_diff(atan2(p.y - yy, p.x - xx), atan2(pt.y - yy, pt.x - xx));
            v = aa/dt * rr;

            if(ut.x >= 0) {
                if(SIGN(yy) == SIGN(aa))
                    v = SIGN(ut.x) * fabs(v);   //check sign with control input
                else
                    return 0;
            } else {
                if(SIGN(yy) != SIGN(aa))
                    v = SIGN(ut.x) * fabs(v);   //check sign with control input
                else
                    return 0;
            }

            w = aa/dt;

            T v2 = v*v;
            T w2 = w*w;
            T r = min_angle_diff(w, (pt.a - p.a)/dt);


            T p0 = stat_pdf_normal_dist(var[0]*v2 + var[1]*w2, 0.0, v - ut.x);
            T p1 = stat_pdf_normal_dist(var[2]*v2 + var[3]*w2, 0.0, min_angle_diff(ut.y, w));
            T p2 = stat_pdf_normal_dist(var[4]*v2 + var[5]*w2, 0.0, r);

            return p0 * p1 * p2;
        }


        /**
         * Sample base velocity motion model for sampling pose \f$x_t = (x',y',\theta')^T\f$
         * from give initial pose and control.
         * @param ut control \f$(v, w)^T\f$
         * @param p initial pose \f$(x, y, \theta)^T\f$
         * @param dt update time
         * @param var robot specific motion error parameters \f$(\sigma_1 ... \sigma_6) \f$
         * @return pose \f$x_t = (x',y',\theta')^T\f
         */
        template<typename T>
        pose2<T> velocity_model_sample(vec2<T> ut,
                                       pose2<T> p,
                                       T dt,
                                       T var[6])
        {
            T v2 = SQR(ut.x);
            T w2 = SQR(ut.y);
            T v = ut.x + stat_sample_normal_dist(var[0]*v2 + var[1]*w2);
            T w = ut.y + stat_sample_normal_dist(var[2]*v2 + var[3]*w2);
            T r = stat_sample_normal_dist(var[4]*v2 + var[5]*w2);

            T x, y, a, v_w;
            if(w != 0) {
                v_w = v/w;
                x = p.x - v_w*sin(p.a) + v_w*sin(p.a + w*dt);
                y = p.y + v_w*cos(p.a) - v_w*cos(p.a + w*dt);
                a = norm_a_rad(p.a + w*dt + r*dt);
            } else {
                x = p.x + v*cos(p.a);
                y = p.y + v*sin(p.a);
                a = norm_a_rad(p.a + r*dt);
            }
            return pose2<T>(x, y, a);
        }

        /**
         * Odometry motion model
         * @param pt
         * @param u_pt
         * @param u_p
         * @param p
         * @param var
         * @return
         */
        template<typename T>
        T odometry_motion(pose2<T> pt,
                          pose2<T> u_pt,
                          pose2<T> u_p,
                          pose2<T> p,
                          T var[6])
        {
            T rot1 = min_angle_diff(u_p.a, atan2(u_pt.y - u_p.y, u_pt.x - u_p.x));
            T tran = (u_pt.vec() - u_p.vec()).size();
            T rot2 = min_angle_diff(rot1, min_angle_diff(u_p.a, u_pt.a));

            T nrot1 = min_angle_diff(p.a, atan2(pt.y - p.y, pt.x - p.x));
            T ntran = (pt.vec() - p.vec()).size();
            T nrot2 = min_angle_diff(nrot1, min_angle_diff(p.a, pt.a));

            T nrot1_sqr = SQR(nrot1);
            T ntran_sqr = SQR(ntran);
            T nrot2_sqr = SQR(nrot2);

            T p0 = stat_pdf_normal_dist(var[0]*nrot1_sqr + var[1]*ntran_sqr, 0.0, min_angle_diff(nrot1, rot1));
            T p1 = stat_pdf_normal_dist(var[2]*ntran_sqr + var[3]*nrot1_sqr + var[3]*nrot2_sqr , 0.0, tran - ntran);
            T p2 = stat_pdf_normal_dist(var[0]*nrot2_sqr + var[1]*ntran_sqr, 0.0, min_angle_diff(nrot2, rot2));

            return p0 * p1 * p2;
        }

        /**
         * Sample based odometry motion model
         * @param u_pt
         * @param u_p
         * @param p
         * @param var
         * @return
         */
        template<typename T>
        pose2<T> odometry_motion_sample(pose2<T> u_pt,
                                        pose2<T> u_p,
                                        pose2<T> p,
                                        T var[4])
        {
            T rot1 = min_angle_diff(u_p.a, atan2(u_pt.y - u_p.y, u_pt.x - u_p.x));
            T tran = (u_pt.vec() - u_p.vec()).size();
            T rot2 = min_angle_diff(rot1, min_angle_diff(u_p.a, u_pt.a));

            T rot1_sqr = LB_SQR(rot1);
            T tran_sqr = LB_SQR(tran);
            T rot2_sqr = LB_SQR(rot2);

            T nrot1 = rot1 + stat_sample_normal_dist(var[0]*rot1_sqr + var[1]*tran_sqr);
            T ntran = tran + stat_sample_normal_dist(var[2]*tran_sqr + var[3]*rot1_sqr + var[3]*rot2_sqr);
            T nrot2 = rot2 + stat_sample_normal_dist(var[0]*rot2_sqr + var[1]*tran_sqr);

            T x = p.x + ntran*cos(p.a + nrot1);
            T y = p.y + ntran*sin(p.a + nrot1);
            T a = norm_a_rad(p.a + nrot1 + nrot2);
            return pose2<T>(x, y, a);
        }

    }





    /*-----------------------------------------------------------
     *
     * Definition of the LibRobotics: Polar Scan Match Algorithm
     * (http://www.irrc.monash.edu.au/adiosi/downloads.html)
     *
     -----------------------------------------------------------*/


    struct lrf_psm_cfg {
        lrf_psm_cfg() :
            scale(1000),        //scale factor from 1 m
            maxError(1*scale),
            searchWndAngle(LB_DEG2RAD(20)),
            lrfMaxRange(4*scale),
            lrfMinRange(0.1*scale),
            minValidPts(50),
            maxIter(20),
            smallCorrCnt(5)

        { }
        double scale;
        double maxError;
        double searchWndAngle;
        double lrfMaxRange;
        double lrfMinRange;
        int minValidPts;
        int maxIter;
        int smallCorrCnt;

    };

    /**
     * Polar Scan-match function for Albert Diosi
     * http://www.irrc.monash.edu.au/adiosi/downloads.html
     *
     * @param ref_robot_pose
     * @param ref_laser_pose
     * @param ref_scan_ranges
     * @param refbad
     * @param refseg
     * @param act_robot_pose
     * @param act_laser_pose
     * @param act_scan_ranges
     * @param actbad
     * @param actseg
     * @param pm_fi
     * @param pm_co
     * @param pm_si
     * @param cfg
     * @param rel_laser_pose
     * @param rel_robot_pose
     * @param force_check
     * @return
     */
    template <typename T, typename T2>
    bool lrf_psm(const pose2<T>& ref_robot_pose,
                 const pose2<T>& ref_laser_pose,
                 const std::vector<T2>& ref_scan_ranges,
                 const std::vector<unsigned int>& refbad,
                 const std::vector<int>& refseg,
                 const pose2<T>& act_robot_pose,
                 const pose2<T>& act_laser_pose,
                 const std::vector<T2>& act_scan_ranges,
                 const std::vector<unsigned int>& actbad,
                 const std::vector<int>& actseg,
                 const std::vector<T>& pm_fi,      //angle lookup table
                 const std::vector<T>& pm_co,      //cosine lookup table
                 const std::vector<T>& pm_si,      //sine lookup table
                 const lrf_psm_cfg& cfg,
                 pose2<T>& rel_laser_pose,           //scan match result
                 pose2<T>& rel_robot_pose,
                 bool force_check = true)           //scan match result)
    {
        vec2<T> relRbPose = ref_robot_pose.vec_to(act_robot_pose).rot(-ref_robot_pose.a);
        T relRbTheta = act_robot_pose.a -ref_robot_pose.a;

        //transformation of actual scan laser scanner coordinates into reference
        //laser scanner coordinates
        vec2<T> actLrfPose = relRbPose + act_laser_pose.vec().rot(relRbTheta);
        T actLrfTheta = relRbTheta + act_laser_pose.a;

        vec2<T> relLrfPose = actLrfPose - ref_laser_pose.vec();
        T relLrfTheta = norm_a_rad(actLrfTheta - ref_laser_pose.a);

        std::vector<T2> refranges(ref_scan_ranges);
        std::vector<T2> actranges(act_scan_ranges);

        //some variables
        size_t nPts = refranges.size();
        std::vector<T> r(nPts, 0);
        std::vector<T> fi(nPts, 0);
        std::vector<T> new_r(nPts, 0);
        std::vector<unsigned int> new_bad(nPts, ERR_EMPTY);
        std::vector<int> index(nPts, 0);

        double angleStep = pm_fi[1] - pm_fi[0];
        int small_corr_cnt = 0;
        int iter = -1;
        int n = 0;//, n2 = 0;
        T dx = 0, dy = 0, dth = 0;
        T ax = relLrfPose.x,  ay = relLrfPose.y, ath = relLrfTheta;
        T delta = 0, x = 0, y = 0, xr = 0, yr = 0;
        T abs_err = 0;
        T ri = 0;
        int idx = 0;
        size_t i = 0;
        T C = LB_SQR(0.7 * cfg.scale);

        while((++iter < cfg.maxIter) && (small_corr_cnt < cfg.smallCorrCnt)) {

            if(iter > 10) C = (1 * cfg.scale);

            T corr = fabs(dx)+fabs(dy)+fabs(dth);

            if(corr < (0.001 * cfg.scale)) {
                small_corr_cnt++;
            }
            else
                small_corr_cnt = 0;

            // convert range readings into ref frame
            // this can be speeded up, by connecting it with the interpolation
            for(i = 0; i < nPts; i++)
            {
                delta   = ath + pm_fi[i];
                xr = (act_scan_ranges[i] * cos(delta));
                yr = (act_scan_ranges[i] * sin(delta));
                x       = xr + ax;
                y       = yr + ay;
                r[i]    = sqrt((x*x)+(y*y));
                fi[i]   = atan2(y,x);
                new_r[i]  = 1e6;            //initialize big interpolated r;
                new_bad[i] = ERR_EMPTY;
            }//for i

            //------------------------INTERPOLATION------------------------
            //calculate/interpolate the associations to the ref scan points

            for(i = 1; i < nPts; i++) {
                // i and i-1 has to be in the same segment, both shouldn't be bad
                // and they should be bigger than 0
                if( actseg[i] >= 0 &&                           //is a segment
                    actseg[i] == actseg[i-1] &&                 //same segment
                    actranges[i] > 0 &&                         //has a measurement
                    (actbad[i] == 0) && (actbad[i-1] == 0))     //is a good measurement
                {
                    //calculation of the "whole" parts of the angles
                    T fi0 = 0, fi1 = 0;
                    T r0 = 0, r1 = 0, a0 = 0, a1 = 0;
                    bool occluded = false;

                    //are the points visible?
                    if(fi[i] > fi[i-1]) {
                        occluded = false;
                        a0  = fi[i-1];
                        a1  = fi[i];
                        fi0 = fi[i-1];//fi0 is the meas. angle!
                        fi1 = fi[i];
                        r0  = r[i-1];
                        r1  = r[i];
                    } else {
                        //invisible - still have to calculate to filter out points which
                        occluded = true; //are covered up by these!
                        //flip the points-> easier to program
                        a0  = fi[i];
                        a1  = fi[i-1];
                        fi0 = fi[i];
                        fi1 = fi[i-1];
                        r0  = r[i];
                        r1  = r[i-1];
                    }

                    //interpolate for all the measurement bearings between fi0 and fi1

                    while(fi0 <= fi1)//if at least one measurement point difference, then ...
                    {
                        //linear interpolate by r and theta ratio
                        ri = (((r1-r0)/(a1-a0))*(fi0 - a0)) + r0;

                        //if fi0 -> falls into the measurement range and ri is shorter
                        //than the current range then overwrite it
                        idx = (int)(fi0/angleStep);
                        idx += (nPts/2);
                        if((idx < (int)nPts) && new_r[idx]>ri) {
                            new_r[idx]    = ri; //overwrite the previous reading
                            index[idx]    = i;  //store which reading was used at index fi0

                            new_bad[idx]  &= ~ERR_EMPTY;    //clear the empty flag

                            //check if it was occluded
                            if(occluded) {
                                new_bad[idx] = ERR_OCCLUDED;//set the occluded flag
                            } else {
                                new_bad[idx] = ERR_NONE;
                            }

                            //the new range reading also it has to inherit the other flags
                            new_bad[idx] |= actbad[i];
                            new_bad[idx] |= actbad[i-1];
                        }
                        fi0 += angleStep;//check the next measurement angle!
                    }//while
                }//if
            }//for

            //---------------ORIENTATION SEARCH-----------------------------------
            //search for angle correction using cross correlation
            if((iter % 2) == 0) {
                T e;
                std::vector<T> err;         // the error rating
                std::vector<T> beta;        // angle for the corresponding error
                int ii = 0;
                int min_i = 0, max_i = 0;
                int wnd = (int)(cfg.searchWndAngle / angleStep);
                T dr;

                for(int di = -wnd ; di <= wnd; di++) {
                    n = 0; e = 0;
                    min_i = LB_MAX(-di, 0);
                    max_i = LB_MIN(nPts, nPts-di);
                    for(ii = min_i; ii < max_i; ii++)//searching through the actual points
                    {
                        if((new_bad[ii] == 0) &&
                           (refbad[ii+di] == 0))
                        {
                            dr = fabs(new_r[ii]-refranges[ii+di]);
                            e += dr;
                            n++;
                        }
                    }//for i

                    if(n > 0)
                        err.push_back(e/n);
                    else
                        err.push_back(1e6); //very large error
                    beta.push_back(di*angleStep);
                }//for di

                //now search for the global minimum
                //assumption: monomodal error function!
                T emin = 1e6;
                int imin = 0;
                for(i = 0; i < err.size(); i++) {
                    if(err[i] < emin) {
                        emin = err[i];
                        imin = i;
                    }
                }

                if(err[imin] >= 1e6)
                {
                    warn("lrf_psm: orientation search failed: %f", err[imin]);
                    dx = 10;
                    dy = 10;
                    if(force_check) {
                        warn("lrf_psm: force check");
                        continue;
                    }
                    else
                        return false;
                } else {
                    dth = beta[imin];
                    if(imin >= 1 && (imin < (int)(beta.size()-1)) &&
                       err[imin-1] < 1e6 && err[imin+1] < 1e6 ) //is it not on the extreme?
                    {//lets try interpolation
                        T D = err[imin-1] + err[imin+1] - 2.0*err[imin];
                        T d = 1000;
                        if((fabs(D) > 0.01) &&
                           (err[imin-1] > err[imin]) &&
                           (err[imin+1] > err[imin]))
                        {
                            d = ((err[imin-1] - err[imin+1]) / D) / 2.0;
//                            warn("lrf_psm: Orientation refinement: %f ", d);
                        }
                        if(fabs(d) < 1) {
                            dth += d * angleStep;
                        }
                        ath += dth;
                    }
                }
                continue;
            }//if

            //-----------------translation-------------
            // do the weighted linear regression on the linearized ...
            // include angle as well
            T hi1, hi2, hwi1, hwi2, hw1 = 0, hw2 = 0, hwh11 = 0;
            T hwh12 = 0, hwh21 = 0, hwh22 = 0, w;
            T dr;
            abs_err = 0;
            n = 0;
            for (i = 0; i < nPts; i++) {
                dr = refranges[i] - new_r[i];

                //weight calculation
                if (refbad[i] == 0 &&
                    new_bad[i] == 0 &&
                    refranges[i] > 0 &&
                    new_r[i] > 0 &&
                    new_r[i] < cfg.lrfMaxRange &&
                    new_r[i] > cfg.lrfMinRange &&
                    fabs(dr) < cfg.maxError )
                {
                    n++;
                    abs_err += fabs(dr);
                    w = C / (dr * dr + C);

                    //proper calculations of the jacobian
                    hi1 = pm_co[i];
                    hi2 = pm_si[i];

                    hwi1 = hi1 * w;
                    hwi2 = hi2 * w;

                    //par = (H^t*W*H)^-1*H^t*W*dr
                    hw1 += hwi1 * dr;//H^t*W*dr
                    hw2 += hwi2 * dr;

                    //H^t*W*H
                    hwh11 += hwi1 * hi1;
                    hwh12 += hwi1 * hi2;
                    //hwh21 += hwi2*hi1; //should take adv. of symmetricity!!
                    hwh22 += hwi2 * hi2;
                }
            }//for i

            if(n < cfg.minValidPts) {
                warn("lrf_psm: Not enough points for linearize: %d", n);
                dx = 10;
                dy = 10;
                if(force_check){
                    warn("Polar Match: force check");
                    continue;
                }
                else
                    return false;
            }

            //calculation of inverse
            T D;//determinant
            T inv11,inv21,inv12,inv22;//inverse matrix
            D = (hwh11*hwh22) - (hwh12*hwh21);
            if(D < 0.001)
            {
                warn("lrf_psm: Determinant too small: %f", D);
                dy = 10;
                dy = 10;
                if(force_check){
                    warn("lrf_psm: force check");
                    continue;
                }
                else
                    return false;
            }

            inv11 =  hwh22/D;
            inv12 = -hwh12/D;
            inv21 = -hwh12/D;
            inv22 =  hwh11/D;

            dx = inv11*hw1+inv12*hw2;
            dy = inv21*hw1+inv22*hw2;

            ax += dx;
            ay += dy;
        }//while

        rel_laser_pose.x = ax;
        rel_laser_pose.y = ay;
        rel_laser_pose.a = ath;

        warn("!!!lrf_psm: rel_robot_pose still not compute!!!");

        return true;
    }



    namespace slam {

        /*-------------------------------------------------
         *
         * Definition of the LibRobotics: DPSLAM Algorithm
         * (http://www.openslam.org/dpslam.html)
         *
         -------------------------------------------------*/

        namespace dpslam {

        }

        /*----------------------------------------------------
         *
         * Definition of the LibRobotics: GridSLAM Algorithm
         * (http://www.openslam.org/gridslam.html)
         *
         ----------------------------------------------------*/

        namespace gridslam {
//            struct grid_line_t{
//              int                   numgrids;
//              std::vector<vec2i>    grid;
//              grid_line_t() :
//                  numgrids(0)
//              { }
//            } ;
//
//            struct QUAD_TREE {
//                struct QUAD_TREE*   elem[4];
//                vec2i               center;
//                unsigned char       level;
//                bool                inuse;
//            };
//
//            template<typename T> struct gridmap2 {
//                QUAD_TREE                           qtree;
//                pose2<T>                            offset;
//                T                                   resolution;
//                std::vector<std::vector<bool> >     updated;
//                std::vector<std::vector<T> >        maphit;
//                std::vector<std::vector<int> >      mapsum;
//                std::vector<std::vector<T> >        mapprob;
//                std::vector<std::vector<T> >        calc;
//                vec2i                               mapsize;
//                vec2<T>                             center;
//
//                bool inline isInside(int x, int y) {
//                    return (x >= 0) && (x < mapsize.x) && (y >= 0) && (y < mapsize.y);
//                }
//            };
        }

        /*----------------------------------------------------
         *
         * Definition of the LibRobotics: EKF SLAM in 2D space
         *
         ----------------------------------------------------*/

        namespace ekf_slam2D {

        }

    }

    /**
     * Namespace for Localization algorithm
     */
    namespace localization {

        /*-------------------------------------------------------------
         *
         * Definition of the LibRobotics: EKF Localization in 2D space
         *
         -------------------------------------------------------------*/
        namespace ekf_feature2 {

        }

        /*-------------------------------------------------------------
         *
         * Definition of the LibRobotics: Monte Carlo Localization MCL in 2D space
         * (for feature map)
         *
         -------------------------------------------------------------*/
        namespace mcl_feature2 {

        }

        /**
         * Namespace for Monte Carlo Localization MCL in 2D grid map
         */
        namespace mcl_grid2 {
            /**
             * Configuration for MCL on grid2 map
             */
            template<typename T>
            struct configuration {
                std::string mapfile;    //!< map file name
                pose2<T> map_offset;    //!< map offset
                vec2<T> map_center;     //!< map center
                T map_res;              //!< map resolution
                T map_angle_res;        //!< pre-compute ray casting angle resolution

                int n_particles;        //!< number of particles
                T min_particels;        //!< in percentage of n_particles \f$(0.0, 1.0)\f$
                T a_slow, a_fast;       //!< decay rate for augmented MCL
                T v_factor;
                T motion_var[6];        //!< \f$(\sigma_0...\sigma_3)\f$ in odometry mode \n \f$(\sigma_0...\sigma_5)\f$ in velocity mode
                T map_var;              //!< compute directly from map resolution
                T z_max_range;          //!< max measurement range
                T z_hit_var;            //!< measurement hit target variance (normal distribution)
                T z_short_rate;         //!< measurement too short rate (exponential distribution)
                T z_weight[4];          //!< normalized weight for all possible measurement outcome


                /**
                 * Simple load a configuration from text file
                 * @param filename
                 */
                void load(const std::string& filename) {
                    std::ifstream file;
                    file.open(filename.c_str());
                    if(!file.is_open()) {
                        throw LibRoboticsIOException("Cannot load file %s in %s", filename.c_str(), __FUNCTION__);
                    }

                    std::string tmp;    //dummy data for load_cfg_from_text_file macro
                    std::cout << "======= mcl_grid2::configuration =======\n";
                    load_cfg_from_text_file(mapfile, file);
                    load_cfg_from_text_file(map_offset, file);
                    load_cfg_from_text_file(map_center, file);
                    load_cfg_from_text_file(map_res, file);
                    load_cfg_from_text_file(map_angle_res, file);
                    map_angle_res = LB_DEG2RAD(map_angle_res);

                    //particles settings
                    load_cfg_from_text_file(n_particles, file);
                    load_cfg_from_text_file(min_particels, file);
                    load_cfg_from_text_file(a_slow, file);
                    load_cfg_from_text_file(a_fast, file);
                    load_cfg_from_text_file(v_factor, file);

                    //motion
                    load_cfg_from_text_file(motion_var[0], file);
                    load_cfg_from_text_file(motion_var[1], file);
                    load_cfg_from_text_file(motion_var[2], file);
                    load_cfg_from_text_file(motion_var[3], file);
                    load_cfg_from_text_file(motion_var[4], file);
                    load_cfg_from_text_file(motion_var[5], file);

                    //measurement
                    load_cfg_from_text_file(z_max_range, file);
                    load_cfg_from_text_file(z_hit_var, file);
                    load_cfg_from_text_file(z_short_rate, file);
                    load_cfg_from_text_file(z_weight[0], file);
                    load_cfg_from_text_file(z_weight[1], file);
                    load_cfg_from_text_file(z_weight[2], file);
                    load_cfg_from_text_file(z_weight[3], file);
                    std::cout << "========================================\n";


                    file.close();
                }
            };

            /**
             * Particle information for MCL on grid2 map
             */
            template<typename T>
            struct particle {
                pose2<T> pose;      //!< robot position
                double w;                //!< weight
                particle() : w(0) { }

                ///Support for output stream operator
                friend std::ostream& operator << (std::ostream& os, const particle<T>& p) {
                    return os << p.pose << " " << p.w;
                }

                ///Support for input stream operator
                friend std::istream& operator >> (std::istream& is, particle<T>& p) {
                    is >> p.pose >> p.w;
                    return is;
                }
            };

            /**
             * Data for MCL on grid2 map
             */
            template<typename T>
            struct data {
                std::vector<mcl_grid2::particle<T> > p;         //!< current particle set
                std::vector<mcl_grid2::particle<T> > p_tmp;     //!< temporary particle set
                map_grid2<T> map;                               //!< gird map
                pose2<T> last_odo_pose;                         //!< last odometry position
                T w_slow;
                T w_fast;

                void initialize(mcl_grid2::configuration<T>& cfg) {
                    p.resize(cfg.n_particles);
                    p_tmp.resize(cfg.n_particles);
                    map.load_image(cfg.mapfile,
                                   cfg.map_offset,
                                   cfg.map_center,
                                   cfg.map_res);
                    w_slow = 0.0;
                    w_fast = 0.0;
                }

                void initialize_particle(int mode, pose2<T> start, T param0, T param1) {
                    size_t i = 0;
                    switch(mode) {
                        case 0: //all at start point
                            for(i = 0; i < p.size(); i++)
                                p[i].pose = start;
                            break;
                        case 1: //case 0 with uniform random angle
                            for(i = 0; i < p.size(); i++) {
                                p[i].pose.x = start.x;
                                p[i].pose.y = start.y;
                                p[i].pose.a = stat_crand() * M_PI;
                            }
                            break;
                        case 2: //all in circle uniform random  at start point
                        {
                            double r, a;
                            for(i = 0; i < p.size(); i++) {
                                stat_sample_circle_uniform_dist(a, r);
                                p[i].pose.x = start.x + (r * param0 * cos(a));
                                p[i].pose.y = start.y + (r * param0 * sin(a));
                                p[i].pose.a = start.a;
                            }
                            break;
                        }
                        case 3: //case 2 with uniform random angle
                        {
                            double r, a;
                            for(i = 0; i < p.size(); i++) {
                                stat_sample_circle_uniform_dist(a, r);
                                p[i].pose.x = start.x + (r * param0 * cos(a));
                                p[i].pose.y = start.y + (r * param0 * sin(a));
                                p[i].pose.a = stat_crand() * M_PI;
                            }
                            break;
                        }
                        case 4: //case 2 with normal distribution random angle around start angle
                        {
                            double r, a;
                            for(i = 0; i < p.size(); i++) {
                                stat_sample_circle_uniform_dist(a, r);
                                p[i].pose.x = start.x + (r * param0 * cos(a));
                                p[i].pose.y = start.y + (r * param0 * sin(a));
                                p[i].pose.a = norm_a_rad(start.a + stat_sample_normal_dist(param1));
                            }
                            break;
                        }
                        case 5: //all uniform random over map
                        {
                            vec2d pts;
                            for(i = 0; i < p.size(); i++) {
                                map.get_random_pts(pts);
                                p[i].pose.x = pts.x;
                                p[i].pose.y = pts.y;
                                p[i].pose.a = start.a;
                            }
                            break;
                        }
                        case 6: //case 5 with uniform random angle
                        {
                            vec2d pts;
                            for(i = 0; i < p.size(); i++) {
                                map.get_random_pts(pts);
                                p[i].pose.x = pts.x;
                                p[i].pose.y = pts.y;
                                p[i].pose.a = stat_crand() * M_PI;
                            }
                            break;
                        }
                        case 7: //case 5 with normal distribution random angle around start angle
                        {
                            vec2d pts;
                            for(i = 0; i < p.size(); i++) {
                                map.get_random_pts(pts);
                                p[i].pose.x = pts.x;
                                p[i].pose.y = pts.y;
                                p[i].pose.a = norm_a_rad(start.a + stat_sample_normal_dist(param1));
                            }
                            break;
                        }
                        case 8:
                        default:
                        {


                            throw LibRoboticsWarningException("This case are not yet implement in %s", __FUNCTION__);
                            break;
                        }
                    }//switch

                    //initialize weight
                    for(i = 0; i < p.size(); i++) {
                        p[i].w = 1.0/p.size();
                    }
                }
            };


            template<typename T>
            int update_with_odomety(mcl_grid2::configuration<T>& cfg,
                                    mcl_grid2::data<T>& data,
                                    std::vector<vec2<T> > z,
                                    pose2<T> odo_pose)
            {
                for(int n = 0; n < cfg.n_particles; n++) {
                    //predict position
                    data.p_tmp[n].pose =
                        math_model::odometry_motion_sample(odo_pose,
                                                           data.last_odo_pose,
                                                           data.p[n].pose,
                                                           cfg.motion_var);
                    //check measurement
                    vec2i grid_coor;
                    T sense_angle = 0;
                    int sense_idx = 0;
                    T zp;

                    if(data.map.get_grid_coordinate(data.p_tmp[n].pose.x, data.p_tmp[n].pose.y, grid_coor)) {
                        if(data.map.ray_casting_cache[grid_coor.x][grid_coor.y].size() != 0) {
                            data.p_tmp[n].w = 1.0;
                            for(size_t i = 0; i < z.size(); i++) {
                            //find nearest measurement in pre-computed ray casting

                                //compute sense angle (convert from local coordinate to global coordinate)
                                sense_angle = norm_a_rad(z[i].theta() + data.p_tmp[n].pose.a);

                                //get index
                                sense_idx = (int)(sense_angle/data.map.angle_res);
                                if(sense_idx < 0) sense_idx += data.map.angle_step;

                                //compute PDF (can speed up by lookup table)
                                zp = math_model::beam_range_finder_measurement(z[i].size(),
                                                                               data.map.ray_casting_cache[grid_coor.x][grid_coor.y][sense_idx],
                                                                               cfg.z_max_range,
                                                                               cfg.z_hit_var,
                                                                               cfg.z_short_rate,
                                                                               cfg.z_weight);
                                data.p_tmp[n].w *= zp;
                            }
                        } else {
                            data.p_tmp[n].w = 0;
                        }

                    } else {
                        data.p_tmp[n].w = 0;
                    }
                    data.p[n].pose = data.p_tmp[n].pose;
                    data.p[n].w = data.p_tmp[n].w;
                }
                data.last_odo_pose = odo_pose;
                return 0;
            }


            template<typename T>
            int update_with_odomety_augmented(mcl_grid2::configuration<T>& cfg,
                                              mcl_grid2::data<T>& data,
                                              std::vector<vec2<T> > z,
                                              pose2<T> odo_pose,
                                              int n_min)
            {
                //=====================================================
                //                    Motion Update
                //=====================================================
                T w_avg = 0.0;
                for(size_t n = 0; n < data.p.size(); n++) {
                    //predict position
                    data.p_tmp[n].pose =
                        math_model::odometry_motion_sample(odo_pose,
                                                           data.last_odo_pose,
                                                           data.p[n].pose,
                                                           cfg.motion_var);
                    //check measurement
                    vec2i grid_coor;
                    T sense_angle = 0;
                    int sense_idx = 0;
                    T zp;

                    if(data.map.get_grid_coordinate(data.p_tmp[n].pose.x, data.p_tmp[n].pose.y, grid_coor)) {
                        if(data.map.ray_casting_cache[grid_coor.x][grid_coor.y].size() != 0) {
                            data.p_tmp[n].w = 1.0;
                            for(size_t i = 0; i < z.size(); i++) {
                            //find nearest measurement in pre-computed ray casting

                                //compute sense angle (convert from local coordinate to global coordinate)
                                sense_angle = norm_a_rad(z[i].theta() + data.p_tmp[n].pose.a);

                                //get index
                                sense_idx = (int)(sense_angle/data.map.angle_res);
                                if(sense_idx < 0) sense_idx += data.map.angle_step;

                                //compute PDF (can speed up by lookup table)
                                zp = math_model::beam_range_finder_measurement(z[i].size(),
                                                                               data.map.ray_casting_cache[grid_coor.x][grid_coor.y][sense_idx],
                                                                               cfg.z_max_range,
                                                                               cfg.z_hit_var,
                                                                               cfg.z_short_rate,
                                                                               cfg.z_weight);
                                data.p_tmp[n].w *= zp;
                            }
                        } else {
                            data.p_tmp[n].w = 0;
                        }

                    } else {
                        data.p_tmp[n].w = 0;
                    }
                    w_avg = w_avg + (data.p_tmp[n].w/data.p.size());
                }

                //update position
                data.last_odo_pose = odo_pose;
                //=====================================================

//                std::sort(data.p_tmp.begin(), data.p_tmp.end(), pf_weight_compare<mcl_grid2::particle<T> >);
//                PRINTVEC(data.p_tmp);


                //=====================================================
                //                       re-sample
                //=====================================================
                size_t np = data.p_tmp.size();

                data.w_slow = data.w_slow + cfg.a_slow*(w_avg - data.w_slow);
                data.w_fast = data.w_fast + cfg.a_fast*(w_avg - data.w_fast);
                T random_prob = LB_MAX(0.0, 1.0 - (cfg.v_factor*(data.w_fast / data.w_slow)));
                int n_random = random_prob * cfg.n_particles;

                PRINTVAR(data.w_slow);
                PRINTVAR(data.w_fast);
                PRINTVAR(random_prob);
                PRINTVAR(n_random);


                pf_normalize_weight(data.p_tmp);
                double square_sum = 0;

                //square sum
                for(size_t i = 0; i < np; i++) {
                   square_sum += LB_SQR(data.p_tmp[i].w);
                }


                int n_eff = (int)(1.0/square_sum);
                PRINTVAR(n_eff);

                if(n_eff > n_min) {
                    data.p = data.p_tmp;
                    return 0;
                }

                PRINTVALUE("Do Resample");

                std::vector<double> cum_sum_w(np, 0.0);
                std::vector<int> keep(np, 0);
                std::vector<double> select(np, 0.0);

                //cumulative sum
                cum_sum_w[0] = data.p_tmp[0].w;
                for(size_t i = 1; i < np; i++) {
                    cum_sum_w[i] = cum_sum_w[i-1] + data.p_tmp[i].w;
                }

                stat_stratified_random(select, np);
                size_t ctr = 0;
                for(size_t i = 0; i < np; i++) {
                    while((ctr < np) && (select[ctr] < cum_sum_w[i])) {
                        keep[ctr] = i;
                        ctr++;
                    }
                }

                for(size_t i = 0; i < np; i++) {
                    data.p[i].pose = data.p_tmp[keep[i]].pose;
                    data.p[i].w = 1.0/np;
                }

                data.last_odo_pose = odo_pose;
                return 1;
            }
        }

        /**
         * Namespace for grid localization in 2D space
         */
        namespace grid2 {
            template<typename T>
            struct grid2_data {

            };


            template<typename T>
            int update(const map_grid2<T>& map) {
                int angle_step = (int)((2.0 * M_PI) / map.angle_res);
                for(int x = 0; x < map.x; x++) {
                    for(int y = 0; y < map.y; y++) {
                        for(int i = 0; i < angle_step; i++) {

                        }
                    }
                }
                return 0;
            }

        }

    }

    namespace path_planning {


        /*-------------------------------------------------------------
         *
         * Definition of the LibRobotics: Vector Field Histogram (VFH) obstacle avoidance
         * (http://www-personal.umich.edu/~johannb/vff&vfh.htm)
         *
         *-------------------------------------------------------------*/

        namespace vfh {
            template <typename T>
            void compute_histogram(const std::vector<vec2<T> >& obs,
                                   T A,
                                   T min_range,
                                   T max_range,
                                   T angle_res_in_degree,
                                   std::vector<T>& h)
            {
                std::vector<vec2<T> > obstacles(obs);
                std::sort(obstacles.begin(), obstacles.end(), compare_vec2_angle<T>);

                T B = A / max_range;

                //search open angle in obstacle list
                T sum = 0.f;
                size_t j = 0;

                int step = (int)(360.0 / angle_res_in_degree) + 1;
                if(step != (int)h.size()) {
                    h.resize(step);
                }

                //compute histogram
                for(int i = 0; (i < step) && (j < obstacles.size()); i++) {
                    while(j < obstacles.size()) {
                        if(obstacles[j].degree_360() > (angle_res_in_degree*(i+1))) {
                            if(sum < 0.f) sum = 0.f;
                            h[i] += sum;
                            sum = 0.f;
                            break;
                        } else {
                            T d = obstacles[j].size();
                            if((d >= min_range) && (d <= max_range)) {
                                T m = (A - (B * d));
                                sum += m;
                            }
                            j++;
                        }//if
                    }//while
                }//for
            }

            template <typename T>
            void smooth_histogram(std::vector<T>& h,
                                  T threshold,
                                  const int smooth_wnd_size)
            {
                std::vector<T> hs(h.size());
                int h_size = h.size();
                int idx;
                T sum = 0;
                for(int i = 0; i < h_size; i++) {
                    sum = 0;
                    for(int l = -smooth_wnd_size; l <= smooth_wnd_size; l++) {
                        idx = i + l;
                        if(idx < 0) {
                            idx = h_size + l;
                        } else if(idx > (h_size - 1)) {
                            idx = l;
                        }

                        if(l < 0)
                            sum += h[idx] * ((smooth_wnd_size + 1) + l);
                        else
                            sum += h[idx] * ((smooth_wnd_size + 1) - l);
                    }
                    sum = sum / (2*smooth_wnd_size + 1);

                    if(sum >= threshold)
                        hs[i] = sum;
                    else
                        hs[i] = 0.f;
                }
                //copy back
                h = hs;
            }

            template <typename T>
            bool find_open_angle(const vec2<T>& target,
                                 const std::vector<T>& hs,
                                 T threshold,
                                 int open_segment,
                                 T angle_res,
                                 vec2<T>& result)
            {
                size_t zero_cnt = 0;
                for(size_t i = 0; i < hs.size(); i++) {
                    if(hs[i] < threshold) {
                        zero_cnt++;
                    }
                }

                //no obstacle, directly move to the target
                if(zero_cnt == hs.size()) {
                    result =  target;
                    return 0;
                }

                //extract open segment
                std::vector<int> k_begin; k_begin.clear();
                std::vector<int> k_end; k_end.clear();
                int count = 0;
                bool is_begin = false;
                int start_step;
                for(int i = 0; i < (int)hs.size(); i++) {
                    if(hs[i] < threshold) {
                        if(is_begin) {
                            count++;
                        } else {
                            is_begin = true;
                            count = 0;
                            start_step = i;
                        }
                    } else {
                        if(is_begin) {
                            k_begin.push_back(start_step);
                            k_end.push_back(start_step + count);
                            is_begin = false;
                            count = 0;
                        }
                    }

                    if(is_begin && (i == (int)(hs.size() - 1))) {
                        k_begin.push_back(start_step);
                        k_end.push_back(start_step + count);
                    }
                }

                //check first and last segment
                if((k_begin[0] == 0) && (k_end[k_end.size() - 1] == (int)(hs.size() - 1))) {
                    //this is the same open segment --> merge them
                    k_end[k_end.size() - 1] = k_end[0];

                    //remove first segment
                    k_begin.erase(k_begin.begin());
                    k_end.erase(k_end.begin());
                }

                int center;
                int good_index = -1;
                vec2<T> good_dir;
                float d_theta = 1e10;
                int  num_subseg = 0;
                bool found = false;

                for(int i = 0; i < (int)k_begin.size(); i++) {
                    num_subseg = -1;
                    if(k_end[i] >  k_begin[i]) {
                        num_subseg = (k_end[i] - k_begin[i]);
                        center =  (k_end[i] +  k_begin[i]) / 2;
                    } else if(k_end[i] <  k_begin[i]) {
                        int tmp1 = hs.size() - k_begin[i];
                        int tmp2 = k_end[i];
                        num_subseg = (tmp1 + tmp2);

                        int tmpCenter = (tmp1 + tmp2) / 2;
                        if((k_begin[i] + tmpCenter) >= (int)hs.size()) {
                            center = k_end[i] - tmpCenter;
                        } else {
                            center = k_begin[i] + tmpCenter;
                        }
                    } else {
                        continue;
                    }

                    T good_angle;
                    vec2<T> dir;
                    float d, c, diff;

                    if(num_subseg >= open_segment) {
                        num_subseg -= open_segment;
                        do {
                            good_angle = (k_begin[i] + (open_segment/2) + num_subseg) * angle_res;
                            good_angle = LB_DEG2RAD(good_angle);
                            dir.x = cos(good_angle);
                            dir.y = sin(good_angle);
                            d = dir ^ target.norm();
                            c = dir * target.norm();
                            diff = fabs(atan2(c,d));
                            if(diff < d_theta) {
                                good_index = i;
                                d_theta = diff;
                                good_dir = dir;
                                found = true;
                            }
                            num_subseg--;
                        } while (num_subseg >= 0);
                    } else {
                        good_angle = LB_DEG2RAD(center * angle_res);
                        dir = vec2<T>(cos(good_angle), sin(good_angle));
                        d = dir ^ target.norm();
                        c = dir * target.norm();
                        diff = fabs(atan2(c,d));
                        if(diff < d_theta) {
                            good_index = i;
                            d_theta = diff;
                            good_dir = dir;
                            found = true;
                        }
                    }//if
                }//for

                if(found)
                    result = good_dir;
                return found;
            }//vfh_find_open_angle

#ifdef librobotics_use_cimg
            template<typename T1, typename T2>
            void draw_histogram_to_cimg(const std::vector<T1>& histogram,
                                            cimg_library::CImg<T2>& img,
                                            const T2 color[],
                                            bool draw_line = false,
                                            float scale = 0.1,
                                            pose2<T1> offset = pose2<T1>(),
                                            bool flip_x = false,
                                            bool flip_y = true)
            {
                using namespace cimg_library;
                int dimx = img.dimx();
                int dimy = img.dimy();
                int xoffset = dimx/2;
                int yoffset = dimy/2;

                CImgList<T1> points;
                float theta_step = (2*M_PI)/histogram.size();
                vec2f pts;
                float x, y;

                for(size_t i = 0; i < histogram.size(); i++) {
                    pts = vec2f(1,0).rotate(theta_step*i) * histogram[i];
                    if(!((offset.x == offset.y) && (offset.y == offset.a) && (offset.a == 0))) {
                        pts = pts.rot(offset.a) + offset.vec();
                    }

                    x = pts.x;
                    if(flip_x) x = -x;
                    x += xoffset;

                    y = pts.y;
                    if(flip_y) y = -y;
                    y += yoffset;

                    points.push_back(CImg<T1>::vector(x, y));
                    img.draw_line(xoffset, yoffset, (int)x, (int)y, color, 0.4f);
                    if(draw_line) {
                        img.draw_line(points, color, 0.8f);
                    }
                }
            }
#endif
        }//vfh
    }//path_planning


}

#endif //#ifndef librobotics_version