#include <gflags/gflags.h>
#include <glog/logging.h>
int main(int argc, char* argv[])
{
    // 解析命令行参数
    // 初始化日志库
    google::InitGoogleLogging(argv[0]);
    FLAGS_log_dir = "./log";

    LOG(INFO) << "Hello, World!";
    return 0;
}
