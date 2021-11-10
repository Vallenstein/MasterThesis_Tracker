// SPDX-License-Identifier: MIT
// Copyright (c) 2020 Manuel Stoiber, German Aerospace Center (DLR)

#include <rbgt/common.h>

namespace rbgt {

    void ReadValueFromFile(std::ifstream &ifs, bool *value) {
        std::string parsed;
        std::getline(ifs, parsed);
        std::getline(ifs, parsed, '\t');
        *value = stoi(parsed);
        std::getline(ifs, parsed);
    }

    void ReadValueFromFile(std::ifstream &ifs, int *value) {
        std::string parsed;
        std::getline(ifs, parsed);
        std::getline(ifs, parsed, '\t');
        *value = stoi(parsed);
        std::getline(ifs, parsed);
    }

    void ReadValueFromFile(std::ifstream &ifs, float *value) {
        std::string parsed;
        std::getline(ifs, parsed);
        std::getline(ifs, parsed, '\t');
        *value = stof(parsed);
        std::getline(ifs, parsed);
    }

    void ReadValueFromFile(std::ifstream &ifs, std::string *value) {
        std::string parsed;
        std::getline(ifs, parsed);
        std::cout << parsed << ";1" << std::endl;
        std::getline(ifs, *value, '\t');
        std::cout << parsed << ";2" << std::endl;
        std::getline(ifs, parsed);
        std::cout << parsed << ";3" << std::endl;

    }

    void ReadValueFromFile(std::ifstream &ifs, Transform3fA *value) {
        std::string parsed;
        std::getline(ifs, parsed);
        Eigen::Matrix4f mat;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                std::getline(ifs, parsed, '\t');
                mat(i, j) = stof(parsed);
            }
            std::getline(ifs, parsed);
        }
        *value = Transform3fA(mat);
    }

    void ReadValueFromFile(std::ifstream &ifs, Intrinsics *value) {
        std::string parsed;
        std::getline(ifs, parsed);
        std::cout << parsed << ";4" << std::endl;
        std::getline(ifs, parsed);
        std::cout << parsed << ";5" << std::endl;
        std::getline(ifs, parsed, '\t');
        value->fu = stof(parsed);
        std::getline(ifs, parsed, '\t');
        value->fv = stof(parsed);
        std::getline(ifs, parsed, '\t');
        value->ppu = stof(parsed);
        std::getline(ifs, parsed, '\t');
        value->ppv = stof(parsed);
        std::getline(ifs, parsed, '\t');
        value->width = stoi(parsed);
        std::getline(ifs, parsed, '\t');
        value->height = stoi(parsed);
        std::getline(ifs, parsed);
    }

// for distCoeffs
    void ReadValueFromFile(std::ifstream &ifs, DistCoeffs *value) {
        std::string parsed;
        std::getline(ifs, parsed);
        std::cout << parsed << ";4" << std::endl;
        std::getline(ifs, parsed);
        std::cout << parsed << ";5" << std::endl;
        std::getline(ifs, parsed, '\t');
        value->k1 = stof(parsed);
        std::getline(ifs, parsed, '\t');
        value->k2 = stof(parsed);
        std::getline(ifs, parsed, '\t');
        value->p1 = stof(parsed);
        std::getline(ifs, parsed, '\t');
        value->p2 = stof(parsed);
        std::getline(ifs, parsed, '\t');
        value->k3 = stoi(parsed);
        std::getline(ifs, parsed);
    }

    void ReadValueFromFile(std::ifstream &ifs, std::filesystem::path *value) {
        std::string parsed;
        std::getline(ifs, parsed);
        std::getline(ifs, parsed, '\t');
        value->assign(parsed);
        std::getline(ifs, parsed);
    }

    void WriteValueToFile(std::ofstream &ofs, const std::string &name, bool value) {
        ofs << name << std::endl;
        ofs << value << "\t" << std::endl;
    }

    void WriteValueToFile(std::ofstream &ofs, const std::string &name, int value) {
        ofs << name << std::endl;
        ofs << value << "\t" << std::endl;
    }

    void WriteValueToFile(std::ofstream &ofs, const std::string &name,
                          float value) {
        ofs << name << std::endl;
        ofs << value << "\t" << std::endl;
    }

    void WriteValueToFile(std::ofstream &ofs, const std::string &name,
                          const std::string &value) {
        ofs << name << std::endl;
        ofs << value << "\t" << std::endl;
    }

    void WriteValueToFile(std::ofstream &ofs, const std::string &name,
                          const Transform3fA &value) {
        ofs << name << std::endl;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                ofs << value.matrix()(i, j) << "\t";
            }
            ofs << std::endl;
        }
    }

    void WriteValueToFile(std::ofstream &ofs, const std::string &name,
                          const Intrinsics &value) {
        ofs << name << std::endl;
        ofs << "f_x, \t f_y, \t pp_x, \t pp_y, \t width, \t height" << std::endl;
        ofs << value.fu << "\t";
        ofs << value.fv << "\t";
        ofs << value.ppu << "\t";
        ofs << value.ppv << "\t";
        ofs << value.width << "\t";
        ofs << value.height << "\t";
        ofs << std::endl;
    }

//for distcoeffs
    void WriteValueToFile(std::ofstream &ofs, const std::string &name,
                          const DistCoeffs &value) {
        ofs << name << std::endl;
        ofs << "k1, \t k2, \t p1, \t p2, \t k3" << std::endl;
        ofs << value.k1 << "\t";
        ofs << value.k2 << "\t";
        ofs << value.p1 << "\t";
        ofs << value.p2 << "\t";
        ofs << value.k3 << "\t";
        ofs << std::endl;
    }

    void WriteValueToFile(std::ofstream &ofs, const std::string &name,
                          const std::filesystem::path &value) {
        ofs << name << std::endl;
        ofs << value.string() << "\t" << std::endl;
    }

    void DrawPointInImage(const Eigen::Vector3f &point_f_camera,
                          const cv::Vec3b &color, const Intrinsics &intrinsics,
                          cv::Mat *image) {
        int u = int(point_f_camera[0] * intrinsics.fu / point_f_camera[2] +
                    intrinsics.ppu + 0.5);
        int v = int(point_f_camera[1] * intrinsics.fv / point_f_camera[2] +
                    intrinsics.ppv + 0.5);
        if (u >= 1 && v >= 1 && u <= image->cols - 2 && v <= image->rows - 2) {
            image->at<cv::Vec3b>(v, u) = color;
            image->at<cv::Vec3b>(v - 1, u) = color;
            image->at<cv::Vec3b>(v + 1, u) = color;
            image->at<cv::Vec3b>(v, u - 1) = color;
            image->at<cv::Vec3b>(v, u + 1) = color;
        }
    }

}  // namespace rbgt
