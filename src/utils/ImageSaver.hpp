#ifndef IMAGESAVER_HPP
#define IMAGESAVER_HPP

#include <QCoreApplication>
#include <QString>
#include <QImage>
#include <QVector>
#include <QDebug>

struct savedImgInfo {
    QString savedImgName;  // 记录当前索引的保存名
    QImage savedImg;  // 保存的图像
};

class ImageSaver {
public:
    // 添加图像和对应的信息
    void addImage(const QImage& image,const QString& name="" ) {
        savedImgInfo info;
        info.savedImgName = name;  // 保存名
        info.savedImg = image;  // 保存图像
        savedImages.append(info);
    }

    // 获取图像信息
    QString getImageName(int index) const {
        if (index >= 0 && index < savedImages.size()) {
            return savedImages[index].savedImgName;
        }
        throw std::out_of_range("Index is out of range.");
    }

    QImage getImage(int index) const {
        if (index >= 0 && index < savedImages.size()) {
            return savedImages[index].savedImg;
        }
        throw std::out_of_range("Index is out of range.");
    }
    // 获取图像数量
    int getImageCount() const {
        return savedImages.size();
    }

    // 打印所有图像信息（用于调试）
    void printAllImages() const {
        for (int i = 0; i < savedImages.size(); ++i) {
            const auto& imgInfo = savedImages[i];
            qDebug() << "Index:" << i << ", Name:" << imgInfo.savedImgName;
        }
    }

    // 根据图像名称获取图像信息
    savedImgInfo getImageInfoByName(const QString& name) const {
        for (const auto& imgInfo : savedImages) {
            if (imgInfo.savedImgName == name) {
                return imgInfo;  // 找到并返回对应的图像信息
            }
        }
        throw std::runtime_error("Image name not found.");
    }

    // 返回所有图像名称
    QStringList getAllImageNames() const {
        QStringList nameList;
        for (const auto& imgInfo : savedImages) {
            nameList.append(imgInfo.savedImgName);
        }
        return nameList;
    }

private:
    QVector<savedImgInfo> savedImages;  // 存储多个图像信息
};
#endif // IMAGESAVER_HPP
