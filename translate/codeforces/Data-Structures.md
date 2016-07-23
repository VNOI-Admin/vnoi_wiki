
# Cấu Trúc Dữ Liệu
**Bài viết chưa hoàn thiện**

Nguồn: [Codeforces](http://codeforces.com/blog/entry/15729)

[[_TOC_]]

## Giới thiệu
Hôm nay, mình muốn giới thiệu tới các bạn một số Cấu trúc dữ liệu hữu ích.
Qua bài viết này, ta sẽ cố gắng nâng cao kỹ năng sử dụng chúng.
Một số CTDL quan trọng:

## Cây
Cây là một trong những CTDL thông dụng và hữu ích nhất. Cây là một đồ thị liên thông không có chu trình. Có nhiều dạng cây như **Cây Có Gốc ( Rooted Trees )**, **Cây Có Hướng ( Directed Trees )**,… 

## Partial Sum
Có 2 dạng bài có thể giải được bằng cách áp dụng Partial Sum.

**Những bài đưa ra các truy vấn yêu cầu cho biết tổng một số phần tử.**

Lời giải cho những bài như thế này như nhau, chỉ cần biết cách giải một trong số chúng.

**Ví dụ:** Cho một mảng **a1,a2,a3,…,aN**. Mỗi truy vấn cho biết 2 số L và R, yêu cầu in ra tổng **aL + a(L+1) + … + aR**. 
**Cách giải:** Tạo một mảng S, với mỗi phần tử **S(i) = a1 + a2 + ..+ a(i) **. Xuất ra:  sR – S(l-1) .


**Những bài yêu cầu thay đổi giá trị các phần tử trong một đoạn.**

Lời giải cho những bài như thế này như nhau, chỉ cần biết cách giải một trong số chúng.

**Ví dụ:** Cho mảng **a1,a2,….aN**. Mỗi truy vấn cho 3 số L,R,V. với mỗi **i ( L<=i<=R )**, cộng **V** vào **a(i)**. Sau khi hoàn thành, in toàn bộ mảng ra.
**Cách giải:**  Tạo một mảng P: **p1,p2,…pN** với mỗi phần tử được khởi tạo với giá trị **0**. Mỗi truy vấn, tăng **p(L)** lên **V** và trừ **p(R+1)** đi V. Sau đó, với mỗi **i ( chạy từ 1 )**, **p(i) += p (i–1).**




