[[_TOC_]]

# FFT

Tác giả: ngmq

Trong bài này chúng ta sẽ tìm hiểu về thuật toán nhân nhanh hai đa thức sử dụng phép biến đổi Fourier nhanh (*Fast Fourier Transform - FFT*) và cách cài đặt của nó. Bài viết này sẽ chỉ nêu chứng minh sơ lược của một vài tính chất được sử dụng. Các chứng minh chi tiết có thể tìm thấy ở mục tài liệu tham khảo phía cuối của bài viết.

# Vài nét lịch sử

Phép biến đổi Fourier (*Fourier Transform*) là một trong số những phát kiến toán học đặc sắc có lịch sử hào hùng, gắn liền với những phát kiến khoa học và chiến tranh quân sự ở thế kỷ 19 và 20. **Joseph Fourier** (1768-1830) là một nhà khoa học làm việc trong đội quân thám hiểm Ai Cập của Napoleon từ năm 1798. Sau khi cách mạng Pháp kết thúc năm 1799, Fourier trở về Pháp và tham gia xây dựng lại đất nước trong vai trò một giáo sư của đại học École Polytechnique. Trong quá trình làm việc với các công trình xây dựng cầu đường và đóng tàu, ông đặc biệt quan tâm tới bài toán mô tả quá trình truyền dẫn nhiệt trong kim loại, điều dẫn tới sự ra đời của phép biến đổi Fourier liên tục vào năm 1807 trong một báo cáo của ông tại viện hoàng gia Paris. Trong đó, ông mô tả mọi hàm số, kể cả các hàm số không liên tục đều có thể được biểu diễn dưới dạng tổng của một số vô hạn các hàm số lượng giác. Phát biểu này của Fourier gây chấn động và ấn tượng tới mức nhà toán học Pháp cùng thời là **Lagrange** cho rằng việc nghĩ ra phát kiến này là "gần như không thể" (*nothing short of impossible*) [1]. Trong hơn một trăm năm sau đó phép biến đổi Fourier trở thành một đối tượng nghiên cứu phổ và liện tục được phát triển, hoàn thiện bởi vô số các tên tuổi lớn của toán lý thuyết [2].

Trong khi phiên bản nguyên thủy có lịch sử hoành tráng như vậy, phép biến đổi Fourier nhanh, dù được cho là ra đời trước, lại được quan tâm chậm hơn nhiều. Người ta cho rằng những ý tưởng đầu tiên về biến đổi Fourier nhanh được phát triển bởi nhà toán học Đức **Carl Friedrich Gauss** (1777 - 1855) vào năm 1805 khi ông cố gắng xác định quỹ đạo của các thiên thạch [3], nhưng ông không công bố kết quả của mình. Mối liên hệ giữa Gauss và phép biến đổi Fourier nhanh chỉ được phát hiện khi các công trình của ông được tập hợp và công bố vào năm 1866. Mặc dù vậy, vào thời đó không có ai quan tâm tới công trình này vì lý thuyết độ phức tạp tính toán chưa phát triển (mãi tới năm 1936 **Alan Turing** mới phát triển mô hình tính toán đầu tiên, và phải tới năm 1965 thì lịch sử ngành nghiên cứu về độ phức tạp tính toán mới bắt đầu với công trình của **Hartmanis** và **Stearns** [4]). Cũng trong năm 1965 hai nhà toán học trong ban cố vấn khoa học của tổng thống Mỹ Kenedy là **James Cooley** và **John Tukey** đã sáng tạo lại phép biến đổi nhanh Fourier trong một nỗ lực nhằm phát hiện các vụ thử hạt nhân của chính quyền Xô Viết [3]. Kể từ thời điểm đó phép biến đổi nhanh Fourier mới chính thức được quan tâm và nghiên cứu ứng dụng trong rất nhiều các lĩnh vực nghiên cứu khác nhau của vật lý, sinh học, điện tử, y tế, điều khiển học...

# Phép nhân hai đa thức

Cho hai đa thức $p(x), q(x)$ có bậc $d, e$ như sau:

$$
p(x) = a_0 + a_1 x + a_2 x^2 + ... + a_d x^d
$$
$$
q(x) = b_0 + b_1 x + b_2 x^2 + ... + b_e x^e
$$

Ta cần tìm tích $c(x)$ của hai đa thức trên, có dạng:
$$
c(x) = p(x)q(x) = c_0 + c_1 x + c_x x^2 + ... + c_{d+e} x^{d+e}
$$

trong đó

$$
c_{j} = \sum_{i=0}^j a_ib_{j-i} \qquad j = 0, 1, ..., d+e
$$

Cách làm theo định nghĩa là ta nhân mỗi hệ số của $p(x)$ với tất cả các hệ số của $q(x)$ rồi cộng các hệ số của cùng tổng số mũ. Vì hai đa thức có $d+1$ và $e+1$ hệ số nên cách làm này có độ phức tạp là $O((d+1)(e+1)) = O(de)$. Khi $d$ và $e$ tương đối lớn cỡ $10^3$ hoặc $10^4$ trở lên thì độ phức tạp này là quá lớn để chạy trên máy tính, đặc biệt là các máy tính nhúng đòi hỏi tốc độ tính toán nhanh. Phép biến đổi FFT giúp thực hiện phép nhân nói trên trong độ phức tạp $O(N*logN)$ trong đó $N$ là lũy thừa của $2$ nhỏ nhất lớn hơn $d$ và $e$.
 
# Biểu diễn đa thức qua ma trận Vandermonde

Xét đa thức $p(x) = a_0 + a_1 x + a_2 x^2 + ... + a_n x^n$ với bậc $n$ và các hệ số phức $a_i \in \mathbb{C}$. Biểu thức tính $n + 1$ giá trị của $p(x)$ tại $n + 1$ điểm $z_0, z_1, ... z_n$ có thể biểu diễn qua phép nhân ma trận như sau: 

$$
\begin{bmatrix}
    1       & z_0^1 & z_0^2 & \dots & z_0^n \newline
       1      & z_1 & z_1^2 & \dots & z_1^n \newline
    \ldots & \ldots & \ldots & \ldots & \ldots\newline
       1       & z_n^1 & z_n^2 & \dots & z_n^n
\end{bmatrix}
\begin{bmatrix}
    a_0 \newline a_1 \newline \vdots  \newline a_n
\end{bmatrix}
=
\begin{bmatrix}
    p(z_0) \newline p(z_1) \newline \vdots  \newline p(z_n)
\end{bmatrix} \space (1)
$$

Ma trận $V$ kích cỡ $(n+1)*(n+1)$ của $z_{0:n}$ ở trên được gọi là ma trận Vandermonde. 
Ta có các định lý sau:

**Định lý 1:** Định thức của ma trận Vandermonde là 
$$det(V) = \prod_{0 \leq i < j \leq n}(z_j - z_i)$$

**Chứng minh (sơ lược):** 
Với mỗi hàng $i = 0, 1, ...n-1$ ta liên tục thay hàng $j = i+1, i+2, ...n$ bằng hiệu của các hệ số của hàng $j$ trừ đi hàng $i$. Đây là phép biến đổi cơ bản nên giá trị định thức cần tính không đổi. Lấy nhân tử chung $z_j - z_i$ ở tất cả các hàng ra ngoài và xét tiếp hàng $i+1$. Sau khi xét xong $i = n-1$ ta được một ma trận chéo có đường chéo chỉ gồm $z_{ii} = 1$. Vì vậy định thức cần tính là tích của tất cả các nhân tử chung bỏ ra ngoài ở các bước trước đó.

Phép chứng minh bằng quy nạp có thể xem thêm tại [đây](https://proofwiki.org/wiki/Vandermonde_Determinant)

**Định lý 2:** Đa thức $p(x)$ được xác định duy nhất bởi giá trị của nó $p(z_0), p(z_1), ... p(z_n)$ với $n+1$ giá trị $z_0, z_1, ... z_n$ phân biệt.

**Chứng minh (sơ lược):** 

Coi phương trình $(1)$ là một hệ phương trình $n+1$ ẩn với bộ nghiệm $a_0, a_1, ...a_n$. Để đa thức $p(x)$ xác định và duy nhất thì định thức của ma trận $V$ ở trên phải khác $0$. Theo **Định lý 1** ta có điều phải chứng minh.

**Hệ quả:** hệ số $a_{0:n}$ được xác định thông qua tích của ma trận nghịch đảo $V^{-1}$ của $V$ và $p(z_{0:n})$.

Từ định lý 2 ta thấy rằng thay vì lưu $n+1$ hệ số $a_i$, ta có thể lưu $(n+1)$ cặp giá trị $z_i, p(z_i)$. Cách biểu diễn bằng giá trị này có lợi thế là giá trị của đa thức tạo bởi tích hai đa thức được tính trong $O(1)$: $c(x) = p(x)q(x)$ trong đó $x$ là một số cho trước.

# Nghiệm nguyên thủy

Ở trên ta đã thấy là các số $z_i$ ở trên có thể chọn tùy ý miễn sao giá trị của chúng là đôi một khác nhau thì đa thức $p(x)$ là xác định và duy nhất. Ý tưởng của thuật toán FFT là chọn các giá trị $z_i$ nào đó để chuyển đổi hai đa thức cần nhân sang miền giá trị, tiến hành phép nhân trong miền giá trị này, tính ma trận nghịch đảo và chuyển đổi ngược lại từ miền giá trị sang miền hệ số. Các giá trị $z$ được chọn phải đặc biệt để các phép tính trên có độ phức tạp nhỏ. Những giá trị đặc biệt này được gọi là **nghiệm nguyên thủy** thỏa mãn:

$$
z^n = 1 \qquad z \in \mathbb{C} (2)
$$

với $n > 0$ nào đó là bậc của đa thức trên và cũng là số nghiệm của phương trình $(2)$ mà ta cần. Công thức Euler xác định nghiệm thứ $k$ của phương trình $(2)$ là

$$
z_k = w_n^k = e^{ {2\pi i}k\over n} = cos{{2\pi k}\over n} + isin{{2\pi k}\over n} \qquad k = 0, 1, ... n - 1
$$

trong đó $w_n^k$ là nghiệm mũ 1:

$$
w_n = e^{ {2\pi i}\over n} = cos{{2\pi}\over n} + isin{{2\pi}\over n}
$$

Dễ thấy là nghiệm nguyên thủy thứ $k$ có thể được tính trong $O(1)$ với $n$ đã biết.

## Một số tính chất đặc biệt của ma trận Vandermonde nghiệm nguyên thủy

# Phép biến đổi Fourier nhanh

Lưu ý là mặc dù hai khái niệm "Biến đổi Fourier rời rạc" (*IDT*) và "Phép biến đổi Fourier nhanh" (*FFT*) là khác nhau nhưng vì khi cài đặt IDT người ta luôn sử dụng FFT nên hai khái niệm này được coi như đồng nhất.

## Công thức truy hồi

Từ tính chất đặc biệt của ma trận $V$ với nghiệm nguyên thủy kể trên, ta có công thức truy hồi để chuyển đổi đa thức có $n$ hệ số (bậc $n-1$) như sau:

# Lưu ý về kỹ thuật cài đặt

## Chuẩn hóa bậc đa thức

## Đệ quy

## Khử đệ quy

## Bài tập ví dụ: POST2-VOJ

# Bài tập luyện tập
- [VOJ POST2](http://vn.spoj.com/problems/POST2/)
- [FFT problems on Codeforces](http://codeforces.com/problemset/tags/fft)
- [FFT problems by a2oj.com](https://a2oj.com/Category.jsp?ID=42)

# Tài liệu tham khảo
- [1] Rohit Thummalapalli. Fourier Transform: Nature’s Way of Analyzing Data. *Yale Scientific*, 2010. [Link](http://www.yalescientific.org/2010/12/fourier-transform-natures-way-of-analyzing-data/)
- [2] Alejandro Dominguez. Highlights in the History of the Fourier Transform. IEEE Pulse, 2016. [Link](http://pulse.embs.org/january-2016/highlights-in-the-history-of-the-fourier-transform/) 
- [3] Stefan Woerner. Fast Fourier Transform. *Numerical Analysis Seminar*, Swiss Federal Institute of Technology Zurich, 2008. [Link](http://www2.math.ethz.ch/education/bachelor/seminars/fs2008/nas/woerner.pdf)
- [4] Fortnow and Homer. A Short History of Computational Complexity. *Bulletin of the European
Association for Theoretical Computer Science 80*, June 2003. [Link](http://people.cs.uchicago.edu/~fortnow/beatcs/column80.pdf)
- [Bài toán nhân đa thức, phép biến đổi Fourier nhanh trên csstudyfun.wordpress.com (có chứng minh các tính chất được đề cập trong bài](https://csstudyfun.wordpress.com/2009/01/12/bai-toan-nhan-da-thuc-phep-bien-doi-fourier-nhanh-fast-fourier-transform-fft/)
- [Bài giảng của trường DH Aalto, Phần Lan](https://drive.google.com/open?id=0BxCwa-q7x3eWT3ZfakNHMWVveTg) 
- [Code cài đặt của e-maxx](http://e-maxx.ru/algo/fft_multiply)
- ["Tutorial on FFT — The tough made simple." trên Codeforces (có phần cơ bản về số phức)](http://codeforces.com/blog/entry/43499)