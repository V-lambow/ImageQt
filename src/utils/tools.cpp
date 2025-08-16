#include "tools.h"
#include "medianfilter.h"

#define min2(a,b) (a)<(b)?(a):(b)
#define min3(a,b,c) min2(min2(a,b),c)


/*****************************************************************************
 *                           Greyscale
 * **************************************************************************/
QImage Tools::GreyScale(QImage origin)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            int average = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;
            newImage->setPixel(x,y,qRgb(average,average,average));
        }
    }

    return *newImage;

}

/*****************************************************************************
 *                           Adjust color temperature
 * **************************************************************************/
QImage Tools::Warm(int delta, QImage origin)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                  QImage::Format_ARGB32);

    QColor oldColor;
    int r, g, b;

    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            oldColor = QColor(origin.pixel(x,y));

            r = oldColor.red() + delta;
            g = oldColor.green() + delta;
            b = oldColor.blue();
//            qDebug()<<r<<" "<<g<<""<<b;

            // Check if the new values are between 0 and 255
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));
        }
    }
    return *newImage;
}

QImage Tools::Cool(int delta, QImage origin)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                  QImage::Format_ARGB32);

    QColor oldColor;
    int r, g, b;

    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            oldColor = QColor(origin.pixel(x,y));

            r = oldColor.red();
            g = oldColor.green();
            b = oldColor.blue() + delta;

            // Check if the new values are between 0 and 255
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));
        }
    }
    return *newImage;
}



/*****************************************************************************
 *                          Adjust image brightness
 * **************************************************************************/
QImage Tools::Brightness(int delta, QImage origin)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                  QImage::Format_ARGB32);

    QColor oldColor;
    int r, g, b;

    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            oldColor = QColor(origin.pixel(x,y));

            r = oldColor.red() + delta;
            g = oldColor.green() + delta;
            b = oldColor.blue() + delta;

            // Check if the new values are between 0 and 255
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));
        }
    }
    return *newImage;
}

/*****************************************************************************
 *                                   Flip
 * **************************************************************************/
QImage Tools::Horizontal(const QImage &origin)
{
    QImage *newImage = new QImage(QSize(origin.width(), origin.height()),
                                  QImage::Format_ARGB32);
    QColor tmpColor;
    int r, g, b;
    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            tmpColor = QColor(origin.pixel(x, y));
            r = tmpColor.red();
            g = tmpColor.green();
            b = tmpColor.blue();

            newImage->setPixel(newImage->width()-x-1,y, qRgb(r,g,b));

        }
    }
    return *newImage;
}

QImage Tools::Vertical(const QImage &origin)
{
    QImage *newImage = new QImage(QSize(origin.width(), origin.height()),
                                  QImage::Format_ARGB32);
    QColor tmpColor;
    int r, g, b;
    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            tmpColor = QColor(origin.pixel(x, y));
            r = tmpColor.red();
            g = tmpColor.green();
            b = tmpColor.blue();

            newImage->setPixel(x, newImage->height()-y-1, qRgb(r,g,b));

        }
    }
    return *newImage;
}





/*****************************************************************************
 *                            添加相框
 * **************************************************************************/
QImage Tools::DrawFrame(QImage origin, QImage &frame)
{
    QImage *newImage = new QImage(origin);
    QPainter painter;

    int width = origin.width();
    int height = origin.height();

    QImage tmpFrame = frame.scaled(QSize(width, height));

    painter.begin(newImage);
    painter.drawImage(0, 0, tmpFrame);
    painter.end();

    return *newImage;

}

/*****************************************************************************
 *                           线性灰度变换 y = ax + b
 * **************************************************************************/
QImage Tools::LinearLevelTransformation(const QImage &origin, double _a, double _b)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;
    int grayLevel = 0;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            grayLevel = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;
            int _y = _a*grayLevel + _b;
            // Make sure that the new values are between 0 and 255
            _y = qBound(0, _y, 255);

            newImage->setPixel(x,y,qRgb(_y,_y,_y));
        }
    }
//    qDebug()<<"a:"<<_a<<"\tb:"<<_b;

    return *newImage;
}


/*****************************************************************************
 *                           对数灰度变换
 * **************************************************************************/
QImage Tools::LogGreyLevelTransformation(const QImage &origin, double a, double b)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;
    int grayLevel = 0;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            grayLevel = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;
            int _y = qLn(b+grayLevel)/qLn(a);

            // Make sure that the new values are between 0 and 255
            _y = qBound(0, _y, 255);

            newImage->setPixel(x,y,qRgb(_y,_y,_y));
        }
    }

    return *newImage;
}


/*****************************************************************************
 *                           幂次灰度变换 _y=c*_x^r+b
 * **************************************************************************/
QImage Tools::PowerGreyLevelTransformation(const QImage &origin, double c, double r, double b)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;
    int _x = 0;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            _x = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;
            int _y =c*qPow(_x, r)+b;

            // Make sure that the new values are between 0 and 255
            _y = qBound(0, _y, 255);

            newImage->setPixel(x,y,qRgb(_y,_y,_y));
        }
    }

    return *newImage;
}


/*****************************************************************************
 *                                  指数灰度变换
 * **************************************************************************/
QImage Tools::ExpTransform(const QImage &origin, double b, double c, double a)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;
    int _x = 0;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            _x = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;
            int _y =qPow(b, c*(_x-a));

            // Make sure that the new values are between 0 and 255
            _y = qBound(0, _y, 255);

            newImage->setPixel(x,y,qRgb(_y,_y,_y));
        }
    }

    return *newImage;
}

/*****************************************************************************
 *                                  双阈值灰度变换
 * int option:
 *          0   0-255-0
 *          1   255-0-255
 * **************************************************************************/
QImage Tools::TwoThreshold(const QImage &origin, double t1, double t2, int option)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;
    int _x = 0;
    int _y = 0;
    if (option == 0)
    {
        for (int x=0; x<newImage->width(); x++) {
            for (int y=0; y<newImage->height(); y++) {
                oldColor = QColor(origin.pixel(x,y));
                _x = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;

                if (_x < t1 || _x > t2)
                    _y = 0;
                else
                    _y = 255;


                // Make sure that the new values are between 0 and 255
                _y = qBound(0, _y, 255);

                newImage->setPixel(x,y,qRgb(_y,_y,_y));
            }
        }
    }
    else
    {
        for (int x=0; x<newImage->width(); x++) {
            for (int y=0; y<newImage->height(); y++) {
                oldColor = QColor(origin.pixel(x,y));
                _x = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;

                if (_x>=t1 && _x<=t2)
                    _y = 0;
                else
                    _y = 255;


                // Make sure that the new values are between 0 and 255
                _y = qBound(0, _y, 255);

                newImage->setPixel(x,y,qRgb(_y,_y,_y));
            }
        }
    }

    return *newImage;
}



/*****************************************************************************
 *                                拉伸灰度变换
 * 拉伸变换使用一个分段函数，三个k值
 * **************************************************************************/
QImage Tools::StretchTransform(const QImage &origin,
                               int x1, int x2,
                               double k1, double k2, double k3,
                               double b2, double b3)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;
    int _x = 0;
    int _y = 0;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            _x = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;

            if ( _x<x1)
                _y = k1*_x;
            else if (_x < x2)
                _y = k2*_x + b2;
            else
                _y = k3*_x + b3;


            // Make sure that the new values are between 0 and 255
            _y = qBound(0, _y, 255);

            newImage->setPixel(x,y,qRgb(_y,_y,_y));
        }
    }

    return *newImage;
}


/*****************************************************************************
 *                               简单平滑处理
 * **************************************************************************/
QImage Tools::SimpleSmooth(const QImage &origin)
{
    QImage *newImage = new QImage(origin);

    int kernel[5][5] = {
        {0,0,1,0,0},
        {0,1,3,1,0},
        {1,3,7,3,1},
        {0,1,3,1,0},
        {0,0,1,0,0}
    };
    int kernelSize = 5;
    int sumKernel=27;
    int r,g,b;
    QColor color;

    for(int x=kernelSize/2; x<newImage->width()-kernelSize/2; x++)
    {
        for (int y=kernelSize/2; y<newImage->height()-kernelSize/2; y++)
        {
            r = g = b = 0;
            for (int i=-kernelSize/2; i<=kernelSize/2; i++)
            {
                for (int j=-kernelSize/2; j<=kernelSize/2; j++)
                {
                    color = QColor(origin.pixel(x+i,y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];

                }
            }
            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            newImage->setPixel(x,y,qRgb(r,g,b));

        }
    }
    return *newImage;
}


/*****************************************************************************
 *                                   中值滤波
 * **************************************************************************/
QImage Tools::MeidaFilter(const QImage &origin, int filterRadius)
{
    int imageHeight = origin.height();
    int imageWidth = origin.width();
    MedianFilter medianFilter;
    int* resImageBits = new int[imageHeight * imageWidth];
    medianFilter.applyMedianFilter((int*)origin.bits(), resImageBits, imageHeight, imageWidth, filterRadius);

    QImage destImage((uchar*)resImageBits, imageWidth, imageHeight, origin.format());
//    QPixmap pixRes;
//    pixRes.convertFromImage(destImage);


    return destImage;
}


/*****************************************************************************
 *                                   拉普拉斯锐化
 * **************************************************************************/
QImage Tools::LaplaceSharpen(const QImage &origin)
{

    int width = origin.width();
    int height = origin.height();
    QImage newImage = QImage(width, height,QImage::Format_RGB888);
    int window[3][3] = {0,-1,0,-1,4,-1,0,-1,0};

    for (int x=1; x<width; x++)
    {
        for(int y=1; y<height; y++)
        {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;

            //对每一个像素使用模板

            for(int m=x-1; m<= x+1; m++)
                for(int n=y-1; n<=y+1; n++)
                {
                    if(m>=0 && m<width && n<height)
                    {
                        sumR += QColor(origin.pixel(m,n)).red()*window[n-y+1][m-x+1];
                        sumG += QColor(origin.pixel(m,n)).green()*window[n-y+1][m-x+1];
                        sumB += QColor(origin.pixel(m,n)).blue()*window[n-y+1][m-x+1];
                    }
                }


            int old_r = QColor(origin.pixel(x,y)).red();
            sumR += old_r;
            sumR = qBound(0, sumR, 255);

            int old_g = QColor(origin.pixel(x,y)).green();
            sumG += old_g;
            sumG = qBound(0, sumG, 255);

            int old_b = QColor(origin.pixel(x,y)).blue();
            sumB += old_b;
            sumB = qBound(0, sumB, 255);


            newImage.setPixel(x,y, qRgb(sumR, sumG, sumB));
        }
    }

    return newImage;

}

/*****************************************************************************
 *                              Sobel Edge Detector
 * **************************************************************************/
QImage Tools::SobelEdge(const QImage &origin) {
    double Gx[9] = {
        1.0, 0.0, -1.0,
        2.0, 0.0, -2.0,
        1.0, 0.0, -1.0
    };

    double Gy[9] = {
        -1.0, -2.0, -1.0,
         0.0,  0.0,  0.0,
         1.0,  2.0,  1.0
    };

    QRgb pixel;
    QImage grayImage = GreyScale(origin);
    int height = grayImage.height();
    int width = grayImage.width();
    QImage newImage(width, height, QImage::Format_RGB888);

    float *sobel_norm = new float[width * height];
    float max = 0.0;
    QColor my_color;

    for (int x = 1; x < width - 1; x++) {  // 避免越界，x 从1开始到 width-2
        for (int y = 1; y < height - 1; y++) {  // 避免越界，y 从1开始到 height-2
            double value_gx = 0.0;
            double value_gy = 0.0;

            for (int k = 0; k < 3; k++) {
                for (int p = 0; p < 3; p++) {
                    pixel = grayImage.pixel(x + k - 1, y + p - 1);  // 这是重要的变更
                    value_gx += Gx[p * 3 + k] * qRed(pixel);
                    value_gy += Gy[p * 3 + k] * qRed(pixel);
                }
            }

            sobel_norm[x + y * width] = std::abs(value_gx) + std::abs(value_gy);
            max = sobel_norm[x + y * width] > max ? sobel_norm[x + y * width] : max;
        }
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (max > 0) {  // 避免除以零
                my_color.setHsv(0, 0, 255 - int(255.0 * sobel_norm[i + j * width] / max));
            } else {
                my_color.setHsv(0, 0, 0);  // 如果最大值为零，则设置为黑色
            }
            newImage.setPixel(i, j, my_color.rgb());
        }
    }

    delete[] sobel_norm;
    return newImage;
}

QImage Tools::PrewittEdge(const QImage &origin) {
    if (origin.isNull()) {
        throw std::invalid_argument("Input image is null.");
    }

    int width = origin.width();
    int height = origin.height();

    // 创建新的图像以存储边缘检测结果
    QImage newImage(width, height, QImage::Format_Grayscale8);

    // 遍历每个像素，避免处理边缘像素
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int gx = 0; // 水平梯度
            int gy = 0; // 垂直梯度

            // 应用 Prewitt 卷积核
            for (int j = -1; j <= 1; ++j) {
                for (int i = -1; i <= 1; ++i) {
                    QColor color(origin.pixel(x + i, y + j));
                    int gray = (color.red() * 299 + color.green() * 587 + color.blue() * 114) / 1000; // NTSC 灰度计算

                    if (i == -1) {
                        gx -= gray; // 左侧
                    } else if (i == 1) {
                        gx += gray; // 右侧
                    }
                    if (j == -1) {
                        gy -= gray; // 上侧
                    } else if (j == 1) {
                        gy += gray; // 下侧
                    }
                }
            }

            // 计算梯度幅度
            int magnitude = static_cast<int>(std::sqrt(gx * gx + gy * gy));
            if (magnitude < 0) {
                magnitude = 0;
            } else if (magnitude > 255) {
                magnitude = 255;
            }
            // 设置新图像的像素值
            newImage.setPixel(x, y, qRgb(magnitude, magnitude, magnitude));
        }
    }

    // 处理边缘像素（可选，设置为 0 或其他值）
    // 取消注释以设置边缘为黑色（可选）
    // newImage.fill(Qt::black);

    return newImage;
}




/*****************************************************************************
 *                                  高斯平滑
 * **************************************************************************/
QImage Tools::GaussianSmoothing(const QImage &origin, int radius, double sigma)
{

    GaussianBlur *blur = new GaussianBlur(radius, sigma);
    QImage newImage = blur->BlurImage(origin);

    return newImage;
}

/*****************************************************************************
 *                                 二值化
 * **************************************************************************/
QImage Tools::Binaryzation(const QImage &origin)
{


    int width = origin.width();
    int height = origin.height();
    QImage newImg = QImage(width, height, QImage::Format_RGB888);

    for (int x=0; x<width; x++)
    {
        for(int y=0; y<height; y++)
        {
            int gray = qGray(origin.pixel(x,y));
            int newGray;
            if (gray > 128)
                newGray = 255;
            else
                newGray = 0;
            newImg.setPixel(x,y,qRgb(newGray, newGray, newGray));
        }
    }
    return newImg;
}


/*****************************************************************************
 *                                 金属拉丝效果
 * **************************************************************************/
QImage Tools::Metal(QImage origin)
{
    QImage *baseImage = new QImage(":/img/src/metal.png");
    QImage darkImage = Tools::Brightness(-100, origin);
    QImage greyImage = Tools::GreyScale(darkImage);
    QPainter painter;

    QImage newImage = baseImage->scaled(QSize(origin.width(),origin.height()));

    painter.begin(&newImage);
    painter.setOpacity(0.5);
    painter.drawImage(0, 0, greyImage);
    painter.end();

    return newImage;
}


/*****************************************************************************
 *                                 轮廓提取法
 * **************************************************************************/
QImage Tools::ContourExtraction(const QImage &origin)
{
    int width = origin.width();
    int height = origin.height();
    int pixel[8];   // 当前像素周围的8个像素的像素值
//    int *pixel = new int[9];
    QImage binImg = Binaryzation(origin);
    QImage newImg = QImage(width, height, QImage::Format_RGB888);
    newImg.fill(Qt::white);

    for(int y=1; y<height; y++)
    {
        for(int x=1; x<width; x++)
        {
            memset(pixel,0,8);

            if (QColor(binImg.pixel(x,y)).red() == 0)
            {
                newImg.setPixel(x, y, qRgb(0,0,0));
                pixel[0] = QColor(binImg.pixel(x-1,y-1)).red();
                pixel[1] = QColor(binImg.pixel(x-1,y)).red();
                pixel[2] = QColor(binImg.pixel(x-1,y+1)).red();
                pixel[3] = QColor(binImg.pixel(x,y-1)).red();
                pixel[4] = QColor(binImg.pixel(x,y+1)).red();
                pixel[5] = QColor(binImg.pixel(x+1,y-1)).red();
                pixel[6] = QColor(binImg.pixel(x+1,y)).red();
                pixel[7] = QColor(binImg.pixel(x+1,y+1)).red();
                if (pixel[0]+pixel[1]+pixel[2]+pixel[3]+pixel[4]+pixel[5]+pixel[6]+pixel[7] == 0)
                    newImg.setPixel(x,y,qRgb(255,255,255));
            }
        }
    }

    return newImg;
}



/*****************************************************************************
 *                                 全方位腐蚀
 * **************************************************************************/
QImage Tools::Dilate(const QImage &origin){
    int width = origin.width();
    int height = origin.height();
    QImage newImg = QImage(width, height, QImage::Format_RGB888);

    int dilateItem[9] = {1,0,1,
                         0,0,0,
                         1,0,1};

    for (int x=1; x<width-1; x++)
    {
        for(int y=1; y<height-1; y++)
        {
            newImg.setPixel(x,y,qRgb(0,0,0));
            for(int m=0; m<3; m++)
            {
                for(int n=0; n<3; n++)
                {
                    if(dilateItem[m+n] == 1)
                        continue;
                    QColor mColor = origin.pixel(x+(n-1),y+(1-m));
                    if(mColor.red() > 128){
                        newImg.setPixel(x,y,qRgb(255,255,255));
                    }
                }
            }
        }
    }
    return newImg;
}

/*****************************************************************************
 *                                 全方位膨胀
 * **************************************************************************/

QImage Tools::Expansion(const QImage &origin)
{
    int width = origin.width();
    int height = origin.height();
    QImage newImg = QImage(width, height, QImage::Format_RGB888);

    int dilateItem[9] = {1,0,1,
                         0,0,0,
                         1,0,1};

    for (int x=1; x<width-1; x++)
    {
        for(int y=1; y<height-1; y++)
        {
            newImg.setPixel(x,y,qRgb(255,255,255));
            for(int m=0; m<3; m++)
            {
                for(int n=0; n<3; n++)
                {
                    if(dilateItem[m+n] == 1)
                        continue;
                    QColor mColor = origin.pixel(x+(n-1),y+(1-m));
                    if(mColor.red() < 128){
                        newImg.setPixel(x,y,qRgb(0,0,0));
                    }
                }
            }
        }
    }
    return newImg;
}


/*****************************************************************************
 *                                开运算
 * **************************************************************************/
QImage Tools::Opening(const QImage &origin)
{
    QImage afterDilate = Dilate(origin);
    QImage afterExpansion = Expansion(afterDilate);

    return afterExpansion;
}

/*****************************************************************************
 *                                闭运算
 * **************************************************************************/
QImage Tools::Closing(const QImage &origin)
{
    QImage afterExpansion = Expansion(origin);
    QImage afterDilate = Dilate(afterExpansion);

    return afterDilate;
}


//QImage Tools::RGB2HSV(const QImage &origin)
//{
//    int width = origin.width();
//    int height = origin.height();
//    QImage newImg = QImage(width, height, QImage::Format_RGB888);

//    for(int x=0; x<width; x++)
//    {
//        for(int y=0; y<height; y++)
//        {
//            QColor color = origin.pixel(x,y);
////            int hue = color.hue();
//            int hue = 0;
//            color.setHsv(hue, color.saturation(), color.value(), color.alpha());
////            newImg.setPixelColor(x,y,color);
//            newImg.setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
//        }
//    }
//    return newImg;
//}

//QImage Tools::RGB2HSL(const QImage &origin)
//{
//    int width = origin.width();
//    int height = origin.height();
//    QImage newImg = QImage(width, height, QImage::Format_RGB888);

//    for(int x=0; x<width; x++)
//    {
//        for(int y=0; y<height; y++)
//        {
//            QColor color = origin.pixel(x,y);
//            int h = 100;
//            color.setHsl(h, color.saturation(),color.lightness(), color.alpha());
//            newImg.setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
//        }
//    }
//    return newImg;
//}

//QImage Tools::RGB2CMYK(const QImage &origin)
//{
//    int width = origin.width();
//    int height = origin.height();
//    QImage newImg = QImage(width, height, QImage::Format_RGB888);

//    for(int x=0; x<width; x++)
//    {
//        for(int y=0; y<height; y++)
//        {
//            QColor color = origin.pixel(x,y);
//            int h = 100;
////            color.setCmyk(color.cyan(), color.magenta(), color.yellow(), color.black());
//            color.setCmyk(color.cyan(), color.magenta(), 0, color.black());
//            newImg.setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
//        }
//    }
//    return newImg;
//}


QImage Tools::Final(const QImage &origin)
{
    int width  = origin.width()/3;
    int height = origin.height()/3;
    int dilateItem[9] = {1,0,1,
                         0,0,0,
                         1,0,1};



    QImage newImg = QImage(origin.width(), origin.height(), QImage::Format_RGB888);

    for(int x=1; x<width; x++)
    {
        for(int y=1; y<height; y++)
        {
            newImg.setPixel(x,y,qRgb(255,255,255));
            for(int m=0; m<3; m++)
            {
                for(int n=0; n<3; n++)
                {
                    if(dilateItem[m+n] == 1)
                        continue;
                    QColor mColor = origin.pixel(x+(n-1),y+(1-m));
                    if(mColor.red() < 128){
                        newImg.setPixel(x,y,qRgb(0,0,0));
                    }
                }
            }
        }
    }


    // laplace
    int window[3][3] = {{0,-1,0},{-1,4,-1},{0,-1,0}};
    for(int x=width; x<2*width; x++)
    {
        for(int y=1; y<height; y++)
        {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;

            //对每一个像素使用模板
            for(int m=x-1; m<= x+1; m++)
                for(int n=y-1; n<=y+1; n++)
                {
                    if(m>=0 && m<width && n<height)
                    {
                        sumR += QColor(origin.pixel(m,n)).red()*window[n-y+1][m-x+1];
                        sumG += QColor(origin.pixel(m,n)).green()*window[n-y+1][m-x+1];
                        sumB += QColor(origin.pixel(m,n)).blue()*window[n-y+1][m-x+1];
                    }
                }


            int old_r = QColor(origin.pixel(x,y)).red();
            sumR += old_r;
            sumR = qBound(0, sumR, 255);

            int old_g = QColor(origin.pixel(x,y)).green();
            sumG += old_g;
            sumG = qBound(0, sumG, 255);

            int old_b = QColor(origin.pixel(x,y)).blue();
            sumB += old_b;
            sumB = qBound(0, sumB, 255);


            newImg.setPixel(x,y, qRgb(sumR, sumG, sumB));
        }
    }




    return newImg;
}

///图像细化
QImage Tools::Thinning(const QImage &origin){

    if (origin.isNull() || origin.format() != QImage::Format_Grayscale8) {
        throw std::invalid_argument("The input image must be a non-null grayscale image.");
        return origin;
    }

    int width = origin.width();
    int height = origin.height();
    QImage imgCopyed(width, height, QImage::Format_Grayscale8);
    imgCopyed.fill(Qt::black); // Initialize imgCopyed with black

    std::vector<std::vector<int>> binaryImage(height, std::vector<int>(width, 0));

    // Convert QImage to binary representation (1 for white, 0 for black)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            binaryImage[y][x] = (qGray(origin.pixel(x, y)) > 128) ? 1 : 0; // Thresholding
        }
    }

    // Thinning algorithm (Zhang-Suen)
    bool hasChanges;
    do {
        hasChanges = false;
        // Apply the first sub-iteration
        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                if (binaryImage[y][x] == 1 &&
                        (binaryImage[y - 1][x] + binaryImage[y][x + 1] + binaryImage[y + 1][x] +
                         binaryImage[y][x - 1] + binaryImage[y - 1][x - 1] + binaryImage[y - 1][x + 1] +
                         binaryImage[y + 1][x - 1] + binaryImage[y + 1][x + 1]) >= 2 &&
                        (binaryImage[y - 1][x] + binaryImage[y][x + 1] + binaryImage[y + 1][x] +
                         binaryImage[y][x - 1]) == 1) {
                    binaryImage[y][x] = 0; // Mark for removal
                    hasChanges = true;
                }
            }
        }

        // Apply the second sub-iteration
        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                if (binaryImage[y][x] == 1 &&
                        (binaryImage[y - 1][x] + binaryImage[y][x + 1] + binaryImage[y + 1][x] +
                         binaryImage[y][x - 1] + binaryImage[y - 1][x + 1] + binaryImage[y + 1][x + 1] +
                         binaryImage[y - 1][x - 1] + binaryImage[y + 1][x - 1]) >= 2 &&
                        (binaryImage[y - 1][x] + binaryImage[y][x + 1] + binaryImage[y + 1][x] +
                         binaryImage[y][x - 1]) == 1) {
                    binaryImage[y][x] = 0; // Mark for removal
                    hasChanges = true;
                }
            }
        }

    } while (hasChanges);

    // Convert binary representation back to QImage
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            imgCopyed.setPixel(x, y, binaryImage[y][x] == 1 ? qRgb(255, 255, 255) : qRgb(0, 0, 0));
        }
    }

    return imgCopyed;
}
///直线绘制
std::tuple<QImage,double> Tools::PaintLine(const QImage &origin,QLineF line,const double& reslouton,QPainter* painter,QPen pen){

        QImage imgCopyed(origin);
        painter->begin(&imgCopyed);
        painter->setPen(pen);
        painter->drawLine(line);
        painter->setRenderHints(QPainter::Antialiasing);
        double len =line.length();

        pen=QPen(Qt::blue, 4);
        painter->setPen(pen);
        painter->drawText(Tools::midPoint(line.p1(),line.p2()).toPoint(),QString::number(len*reslouton)+"(um)");
        painter->end();

        return std::make_tuple(imgCopyed,len);
}
std::tuple<QImage,double> Tools::PaintLineAPt(const QImage &origin,QLineF line,QPointF pt,const double& reslouton,QString str,QPainter* painter,QPen pen){

    QImage imgCopyed(origin);
     pen.setStyle(Qt::DotLine);
    painter->begin(&imgCopyed);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing);
    painter->drawLine(line);


    float k =(line.y2()-line.y1())*1.0/(line.x2()-line.x1());
    float B=-1.0;
    float C=line.y1()-k*line.x1();
    QPointF pFoot{(B*B*pt.x()-k*B*pt.y()-k*C)/(k*k+B*B),(k*k*pt.y()-k*B*pt.x()-B*C)/(k*k+B*B)};

//    double k=(pt.x()-line.x1())*(line.x2()-line.x1())+\
//            (pt.y()-line.y1())*(line.y2()-line.y1())/\
//            pow((line.x2()-line.x1()),2)+pow(line.y2()-line.y1(),2);
//    painter.drawLine(QPointF(line.x1()+k*(line.x2()-line.x1()),line.y1()+k*(line.y2()-line.y1())),pt);

    pen=QPen(Qt::green, 1);
    pen.setStyle(Qt::SolidLine);

    painter->setPen(pen);
    painter->drawLine(pFoot,pt);
    double len =QLineF(pFoot,pt).length();

    pen=QPen(Qt::blue, 4);
    painter->setPen(pen);
    double lenReal=0.0;
    if(str=="calibration"){
        lenReal = reslouton;
    }
    else{
        lenReal = len*reslouton;
    }
    painter->drawText(Tools::midPoint(pFoot,pt).toPoint(),QString::number(lenReal)+"(um)");
    painter->end();
    return std::make_tuple(imgCopyed,len);

}
std::tuple<QImage,double> Tools::PaintRect1(const QImage &origin,QPointF ptbg,QPointF ptend,const double& reslouton,QPainter* painter,QPen pen){

    QImage imgCopyed(origin);
    painter->begin(&imgCopyed);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing);
    painter->drawRect(QRect(ptbg.toPoint(),ptend.toPoint()));
    int Area =QRect(ptbg.toPoint(),ptend.toPoint()).height()*QRect(ptbg.toPoint(),ptend.toPoint()).width();
    pen=QPen(Qt::blue, 4);
    painter->setPen(pen);
    painter->drawText(Tools::midPoint(ptbg,ptend).toPoint(),QString::number(Area*pow(reslouton,2))+"(um²)");

    painter->end();
    return std::make_tuple(imgCopyed,Area*pow(reslouton,2));
}
std::tuple<QImage,double>  Tools::PaintPoly(const QImage &origin,const QVector<QPointF>pts,const double& reslouton,QPainter* painter,QPen pen){

    QImage imgCopyed(origin);
    painter->begin(&imgCopyed);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing);
    painter->drawPolygon(pts);
    double Area= Tools::calculatePolygonArea(pts);
    pen=QPen(Qt::blue, 4);
    painter->setPen(pen);
    painter->drawText(Tools::midPoint(pts.at(0),pts.at(1)).toPoint(),QString::number(Area*pow(reslouton,2))+"(um²)");
    painter->end();

    return std::make_tuple(imgCopyed,Area*pow(reslouton,2));

}

std::tuple<QImage,double>  Tools::PaintAngle(const QImage &origin,const QVector<QPointF>pts,QPainter* painter,QPen pen){

    QImage imgCopyed(origin);

    painter->begin(&imgCopyed);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing);
    painter->drawLine(pts.at(0),pts.at(1));
    painter->drawLine(pts.at(1),pts.at(2));
    double angle = Tools::pts3toAngle(pts);
    pen=QPen(Qt::blue, 4);
    painter->setPen(pen);
    painter->drawText(Tools::midPoint(pts.at(0),pts.at(1)).toPoint(),QString::number(angle)+"(°)");
    painter->end();

    return std::make_tuple(imgCopyed,angle);

}



/******************************中点求解***********************************/
QPointF Tools::midPoint( QPoint const &pt1,QPoint const &pt2=QPoint(0,0)){

    return QPointF(float((pt1.x() + pt2.x()) / 2), float((pt1.y() + pt2.y()) / 2));
}

QPointF Tools::midPoint( QPointF const &pt1,QPointF const &pt2=QPointF(0.0,0.0)){

    return QPointF(float((pt1.x() + pt2.x()) / 2), float((pt1.y() + pt2.y()) / 2));
}

///凸四边形秦九昭公式
double Tools::calculatePolygonArea(const QVector<QPointF> &points) {
    int n = points.size();
    if (n < 3) {
        qWarning() << "A polygon must have at least 3 points.";
        return 0.0;
    }

    double area = 0.0;

    // 使用叉积计算多边形的面积
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;  // 下一个点的索引，循环回到起点
        area += points[i].x() * points[j].y();
        area -= points[j].x() * points[i].y();
    }

    return qAbs(area) / 2.0;  // 返回绝对值除以2
}


///3点角度求解
double Tools::pts3toAngle(const QVector<QPointF>& points) {
    if (points.size() != 3) {
          throw std::runtime_error("Input must contain exactly 3 points.");  // 使用异常处理来提示错误
      }

      QPointF A = points[0];
      QPointF B = points[1];
      QPointF C = points[2];

      // 计算向量 BA 和 BC
      QPointF BA = B - A;
      QPointF BC = B - C;

      // 计算长度
      double lengthBA = std::sqrt(BA.x() * BA.x() + BA.y() * BA.y());
      double lengthBC = std::sqrt(BC.x() * BC.x() + BC.y() * BC.y());

      // 检查向量长度是否为零
      if (lengthBA == 0.0 || lengthBC == 0.0) {
          return 0; // 如果任一向量的长度为0，返回0度
      }

      // 计算点积
      double dotProduct = BA.x() * BC.x() + BA.y() * BC.y();

      // 计算余弦值
      double cosTheta = dotProduct / (lengthBA * lengthBC);

      // 限制cosTheta在-1到1之间以防浮点误差

      cosTheta =fmin(1.0, std::max(-1.0, cosTheta));

      // 计算夹角（弧度转化为度）
      double angleRad = std::acos(cosTheta);
      double angleDeg = angleRad * (180.0 / M_PI);

      return angleDeg;

}




