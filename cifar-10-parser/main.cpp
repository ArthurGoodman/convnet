#include <QtCore>
#include <QtGui>
#include <iostream>

static const char *imagesDirName = "../images";
static const char *testImagesDirName = "../test_images";

static const int width = 32, height = 32;
static int counter = 0;

void parseFile(const QString &dir, QFile *file) {
    QDataStream stream(file);

    while (!stream.atEnd()) {
        uint8_t label;
        char pixels[width * height * 3];

        stream >> label;
        stream.readRawData(pixels, sizeof(pixels));

        QImage image(width, height, QImage::Format_RGB32);

        QRgb *imageData = (QRgb *)image.scanLine(0);

        for (uint i = 0; i < sizeof(pixels) / 3; i++)
            imageData[i] = qRgb(pixels[i + 0 * sizeof(pixels) / 3], pixels[i + 1 * sizeof(pixels) / 3], pixels[i + 2 * sizeof(pixels) / 3]);

        QString imageName = dir + "/" + QString::number(label) + "-" + QString::number(counter++) + ".bmp";

        image.save(imageName);

        std::cout << imageName.toStdString() << "\n";
    }
}

int main() {
    QDir().mkdir(imagesDirName);
    QDir().mkdir(testImagesDirName);

    for (int i = 1; i <= 5; i++) {
        QFile file("../cifar-10-batches-bin/data_batch_" + QString::number(i) + ".bin");

        if (!file.open(QFile::ReadOnly))
            return 1;

        parseFile(imagesDirName, &file);
        file.close();
    }

    counter = 0;

    QFile file("../cifar-10-batches-bin/test_batch.bin");

    if (!file.open(QFile::ReadOnly))
        return 1;

    parseFile(testImagesDirName, &file);
    file.close();

    return 0;
}
