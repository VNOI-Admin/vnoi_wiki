#Hướng dẫn cài đặt OpenCV trên Windows

[Bài viết gốc](http://dangkhoasdc.github.io/cai-dat-opencv-tren-windows-visual-studio/)

##Biên dịch thư viện OpenCV

Điểm thuận lợi của việc tự cài đặt và biên dịch thư viện có thể kể đến như sau:
1. Hỗ trợ IDE mới nhất, như trong bản OpenCV 3.0 (22/11/2015) thì chưa có bản biên dịch sẵn dành cho VS 2015.
2. Customize được các thư viện khác liên quan như Kinect, OpenCL, Python…

[Link Download thư viện OpenCV cho HĐH Windows](http://downloads.sourceforge.net/project/opencvlibrary/opencv-win/3.0.0/opencv-3.0.0.exe?r=http%3A%2F%2Fopencv.org%2F&ts=1448134045&use_mirror=nchc)

Bước 1: Giải nén thư viện vào thư mục được định sẵn. Giả sử đường dẫn của mã nguồn là C:\opencv

![](http://dangkhoasdc.github.io/images/install_opencv/extract_opencv.png)

Bước 2: Tải và cài đặt CMake. Thư mục build chứa những tập tin của phần mã nguồn được biên dịch sẵn. Phần sources được sử dụng cho cài đặt manual.

![](http://dangkhoasdc.github.io/images/install_opencv/dirs.png)

Bước 3: Mở CMake. Trong phần Where is the source code sẽ trỏ đến thư mục sources đã đề cập lúc trước. Phần Where to build the binaries là nơi chứa phần thư viện được biên dịch. Trong ví dụ này đường dẫn là C:\opencv\source\build.

![](http://dangkhoasdc.github.io/images/install_opencv/cmake.png)

Bước tiếp theo nhấn Configure, sau đó chọn bộ generator cho project, trong phần này sẽ chọn tương ứng với IDE/Compiler mà mã nguồn mình sử dụng. Đồng thời, nếu máy tính đang ở kiến trúc x86 thì chọn các phiên bản IDE với tùy chọn là x86 (Ví dụ Visual Studio 14 2015). Đối với các máy tính kiến trúc x64 thì chọn phiên bản có hậu tố là Win64. Nhấn Finish để kết thúc cấu hình.

Sau khi configure xong thì danh sách các tùy chọn khi biên dịch để hiện ra với rất nhiều tùy biến đi kèm. Phần này trong tutorial này sẽ bỏ qua vì mục tiêu chỉ cần cài đặt bộ thư viện ở mức mặc định là thành công rồi. Nếu không có gì thay đổi ta nhấn chọn Generate.

Sau khi quá trình phát sinh mã nguồn hoàn tất, trong thư mục build sẽ xuất hiện các Project/Solution khác nhau.

Bước 4: Dùng Visual Studio để mở solution có tên là OPENCV. Lưu ý: khi bản VS này phải trùng với bản VS đã configure trong cmake.

![](http://dangkhoasdc.github.io/images/install_opencv/target_arch.png)

##Cấu hình Opencv trên Visual Studio

Bước 1: Tạo một Project (Empty Project).

![](http://dangkhoasdc.github.io/images/install_opencv/new_project.png)

Trước khi thực hiện tiếp các công việc cấu hình cho project. Ta cần xác định rõ sẽ cần cấu hình những thông tin gì:
1. Nơi chứa header file của OpenCV. Dĩ nhiên ta cần làm điều này để include các đối tượng, hàm… của 
2. Cấu hình các file cần thiết khi lập 
3. Cấu hình các file cần thiết cho quá trình thực thi. Bởi trong Visual Studio có 2 target khi run bao gồm Debug và Release, nên ta cần phải cấu hình riêng biệt cho mỗi target đó.

##Cấu hình header file

Click chuột phải vào tên project (InstallOpencv) chọn Properties (Hoặc nhấn Alt + F7).

![](http://dangkhoasdc.github.io/images/install_opencv/include_configure.png)

Phía bên phần Sidebar chọn C/C++, General, mục Additional Include Directories ta trỏ đến thư mục opencv\build\include (không phải sources\build\include). Để đảm bảo ta có thể check bằng cách kiểm tra xem thư mục include đó có các header file không. Xong nhấn OK.

##Cấu hình thư viện cho quá trình lập trình

Nhấn Alt + F7 để vào phần Properties của Project. Chọn Thẻ Linker, mục Additional Library Directories ta trỏ đến thư mục lib\Debug (trong ví dụ này là: C:\oepncv\sources\build\lib\Debug). Vì đang cấu hình cho target là Debug nên phần Configuration phải là Debug

![](http://dangkhoasdc.github.io/images/install_opencv/lib_configuration.png)

Chuyển đến thẻ Input, mục Additional Dependencies ta nhập các file sau:

>opencv_calib3d300d.lib
>opencv_core300d.lib
>opencv_features2d300d.lib
>opencv_flann300d.lib
>opencv_hal300d.lib
>opencv_highgui300d.lib
>opencv_imgcodecs300d.lib
>opencv_imgproc300d.lib
>opencv_ml300d.lib
>opencv_objdetect300d.lib
>opencv_photo300d.lib
>opencv_shape300d.lib
>opencv_stitching300d.lib
>opencv_superres300d.lib
>opencv_ts300d.lib
>opencv_video300d.lib
>opencv_videoio300d.lib
>opencv_videostab300d.lib

Sau khi cấu hình xong, ta chuyển qua target là Release và thực hiện giống hệt như vậy. Tuy nhiên đường dẫn lần này sẽ là sources\build\lib\Release.

Phần Additional Dependencies sẽ là:

>opencv_calib3d300.lib
>opencv_core300.lib
>opencv_features2d300.lib
>opencv_flann300.lib
>opencv_hal300.lib
>opencv_highgui300.lib
>opencv_imgcodecs300.lib
>opencv_imgproc300.lib
>opencv_ml300.lib
>opencv_objdetect300.lib
>opencv_photo300.lib
>opencv_shape300.lib
>opencv_stitching300.lib
>opencv_superres300.lib
>opencv_ts300.lib
>opencv_video300.lib
>opencv_videoio300.lib
>opencv_videostab300.lib

##Cấu hình thư viện cho quá trình thực thi

Khi thực hiện build 1 chương trình, VS sẽ tạo ra trong thư mục của Solution một thư mục với cấu trúc như sau: \Debug và \Release. Trong ví dụ này là x64\Debug, x64\Release. Ta chép toàn bộ file trong build\bin\Debug vào x64\Debug, tương tự như vậy đối với build\bin\Release và x64\Release.

Tạo một file cpp và run thử chương trình.

Mã nguồn:

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main() {
	Mat img = imread("demo.jpg");
	imshow("show image", img);
	waitKey(0);
	destroyAllWindows();
}
```
(Với mã nguồn này lưu ý đặt 1 file tên là demo.jpg vào trong thư mục chứa mã nguồn).

![](http://dangkhoasdc.github.io/images/install_opencv/demo.png)

Kết quả ta được như hình trên.

##Tuy nhiên

Có một chữ tuy nhiên to đùng như vậy vì với cách cấu hình thế này có khá là nhiều bất cập:

1. Mỗi lần tạo 1 project OpenCV mới mà ngồi config (Mục 2) thì cũng rất là mất thời gian. Chưa kể trong lúc cấu hình mà quên mất một công đoạn nào thì có khi đi tong cả buổi chỉ để fix lỗi.
2. Những file trong sources\bin\Debug hay Release đều xấp xỉ 900MB. Vị chi mỗi lần chép qua bên project thì tốn thêm 1.8GB bộ nhớ. Chỉ cần trong máy chứa dăm ba project dùng OpenCV thì sẽ ngốn dung lượng đến chừng nào.
3. Phần Additional Dependencies mỗi phiên bản OpenCV mỗi khác, làm thế nào để lấy được danh sách các file như thế này.

Ta sẽ giải quyết từ dễ đến khó trước.

##Additional Dependencies

Sau khi biên dịch xong thư viện ta mở Command Line và trỏ đến thư mục sources\build\lib

Gõ lệnh sau:
>dir Debug\*d.lib /B >..\DependenciesDebug.txt
>dir Release\*.lib /B >..\DependenciesRelease.txt

Sau khi gõ xong thì trong thư mục build sẽ xuất hiện 2 file text là DependenciesDebug và DependenciesRelease chứa danh sách tât cả các file libs. Mỗi lần sử dụng chỉ cần mở file lên và chép vào.

#Lib Configuration

Mở Command Line (Với quyền Admin - click chuột phải vào biểu tượng Start và chọn Command Promp) và gõ lệnh

>setx -m OPENCV_DIR C:\opencv

Nhấn Windows E để mở Windows Explore

![](http://dangkhoasdc.github.io/images/install_opencv/win_properties.png)

Click vào Computer và chọn Properties

![](http://dangkhoasdc.github.io/images/install_opencv/environment_var.png)

Chọn Advanced system settings. Trong thẻ Advanced chọn Environment Variables…

![](http://dangkhoasdc.github.io/images/install_opencv/path_variable.png)

Điền ngay phía sau của phần Variable value giá trị sau: %OPENCV_DIR%\sources\build\bin\Debug;%OPENCV_DIR%\sources\build\bin\Release

Xong, và từ giờ trở đi ta không cần phải chép các file trong build\bin vào trong project nữa.

##Sao lưu config của project

Trong sidebar Property Manager ta thấy danh sách các config architecture trong project tương ứng với từng target .

![](http://dangkhoasdc.github.io/images/install_opencv/Property_manager.png)

Ta sẽ tạo một Property Sheet mới (Click chuột phải vào từng mục và chọn Add New Project Property Sheet…), double click vào mục mới tạo và cấu hình giống hệt với mục 2. Sau đó lưu lại. VS sẽ tạo ra 1 file có định dạng props trong project. Sau này khi tạo ra 1 project mới ta chỉ cần import Property đã tạo mà không cần config lại từ đầu.

Vì đã set OPENCV_DIR là thư mục của OpenCV nên ta có thể thay đổi đường dẫn của các config thành

>%OPENCV_DIR%\build\include
>%OPENCV_DIR%\source\build\lib\Debug
>%OPENCV_DIR%\source\build\lib\Release
