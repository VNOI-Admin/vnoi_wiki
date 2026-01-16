---
title: Thuật toán sắp xếp
description: 
published: true
date: 2026-01-16T01:04:34.125Z
tags: 
editor: markdown
dateCreated: 2025-12-19T01:32:35.401Z
---

# Sắp xếp

**Người viết:**

- Đoàn Quang Huy - THPT Chuyên Nguyễn Tất Thành, Quãng Ngãi.

**Reviewer:**

- Nguyễn Tiến Mạnh - Đại học Bách khoa Hà Nội.
- Nguyễn Hoàng Dương - Trường Đại học Công nghệ, ĐHQG-HN.
- Nguyễn Tấn Minh - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM.

## Giới thiệu

Sắp xếp là một trong những thuật toán cơ bản và nền tảng của lập trình. Mọi ứng dụng xử lý dữ liệu ở mức tối thiểu đều cần sắp xếp theo một thứ tự nào đó. Ví dụ: 

* Danh bạ điện thoại, danh sách học sinh theo thứ tự từ điển.
* Kết quả tìm kiếm trên Internet.

Ngoài ra, nhiều thuật toán phức tạp hơn (tìm kiếm, loại trùng, tối ưu hóa, hay các kỹ thuật sử dụng tính đơn điệu) đều dựa vào hoặc được đơn giản hóa nhờ dữ liệu đã được sắp xếp.

Trong C++, hàm `std::sort` là công cụ bạn thường dùng: nó sắp xếp mảng, vector theo thứ tự bạn mong muốn và đảm bảo độ phức tạp $\mathcal{O}(n \times \log n)$ trong mọi trường hợp phổ biến.

Bài viết này sẽ làm rõ các thuật toán sắp xếp thường gặp trong thực tế (quicksort, mergesort, heapsort...), so sánh điểm mạnh/yếu của chúng, và đưa ra một số bài toán minh họa, giúp bạn hiểu khi nào nên dùng thuật toán nào và cách vận dụng chúng trong giải thuật.

## Các thuật toán sắp xếp phổ biến
### Sắp xếp chọn (Selection Sort)

#### Ý tưởng

Ban đầu, ta chọn ra phần tử nhỏ nhất trong $n$ phần tử, đưa nó về đầu dãy. Sau đó lặp lại quá trình sắp xếp với phần còn lại của dãy cho đến khi dãy tăng dần. Nói cách khác, với mỗi vị trí $i$, ta sẽ tìm vị trí $j$ $\geq$ $i$ sao cho $a_j$ nhỏ nhất rồi hoán đổi $a_i$ và $a_j$.

#### Cài đặt
:::spoiler Code tham khảo
```cpp=
void selectionSort(int a[], int n){
    for (int i = 0; i < n - 1; i++) {
        int min_pos = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_pos]) {
                min_pos = j;
            }
        }
        swap(a[i], a[min_pos]);
    }
} 
```
:::
Độ phức tạp: $\mathcal{O}(n^2)$.

<center>
<video controls width="80%">
  <source src="/algo/sorting/selectionsort.mp4" type="video/mp4">
</video>
</center>

### Sắp xếp nổi bọt (Bubble Sort)

#### Ý tưởng
Khác với sắp xếp chọn, sắp xếp nổi bọt sẽ so sánh trực tiếp với 2 phần tử liên tiếp. Nếu phần tử đứng trước lớn hơn phần tử đứng sau thì sẽ hoán đổi. Lặp lại cho đến khi dãy tăng dần.

#### Cài đặt

:::spoiler Code tham khảo
```cpp= 
void bubbleSort(int a[], int n){
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }

        // Nếu không có hoán đổi nào, mảng đã được sắp xếp
        if (!swapped) break;
    }
}
 
```
:::
Độ phức tạp: $\mathcal{O}(n^2)$.

#### Nhận xét

> Số lần hoán đổi (swap) của thuật toán bằng đúng số lượng cặp nghịch thế (inversions) của mảng ban đầu. Tức số cặp chỉ số $i, j$ sao cho $a_i > a_j$.

Ta quan sát thấy mỗi lần ta hoán đổi của Bubble Sort sẽ làm **giảm đúng $1$ nghịch thế**. Hơn nữa, dãy cuối cùng đã được sắp xếp là một dãy không có nghịch thế nào. Từ đó, ta có thể kết luận quá trình giảm số nghịch thế xuống $0$ sẽ tốn số lần hoán đổi đúng bằng số nghịch thế ban đầu. 

![BubbleSortScene](https://hackmd.io/_uploads/rk5WMbCCle.gif)

### Sắp xếp chèn (Insertion Sort)

#### Ý tưởng

Ta lặp lại thao tác sắp xếp $n$ lần. Ở lần thứ $k$, ta đã có dãy $k-1$ phần tử đầu tiên đã được sắp xếp. Để mở rộng thành dãy có $k$ phần tử đã được sắp xếp, ta xét $a_{k} = x$ rồi tìm vị trí thích hợp để chèn $x$ vào. Dễ dàng nhận thấy vị trí thích hợp sẽ là vị trí đứng trước một phần tử lớn hơn và sau phần tử nhỏ hơn hoặc bằng nó.

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
void insertionSort(int a[], int n){
    for (int i = 1; i < n; i++) {
        int x = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > x) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;
    }
} 
```
:::
Độ phức tạp: $\mathcal{O}(n^2)$.

![InsertionSortScene](https://hackmd.io/_uploads/S1dd--RCgl.gif)

### Sắp xếp đếm phân phối (Counting Sort)

#### Giới thiệu
Các thuật toán sắp xếp ở trên đều có độ phức tạp $\mathcal{O}{(n^2)}$, nên trong nhiều trường hợp sẽ không đủ nhanh để xử lý dữ liệu lớn. Ở phần này, ta sẽ tìm hiểu một thuật toán có thể đạt hiệu năng tuyến tính trong những điều kiện phù hợp: __Counting Sort__.

#### Ý tưởng
Ta đếm tần suất xuất hiện của các phần tử, sau đó duyệt toàn bộ từ $0$ đến $n$, nếu phần tử xuất hiện thì ta lần lượt in ra $k$ phần tử với $k$ là số lần xuất hiện của $a_{i}$.

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
const int MAXV = 10000000;
int cnt[MAXV + 1];

void countingSort(int a[], int n){
    for (int i = 0; i < n; i++) {
        cnt[a[i]]++;
    }

    int idx = 0;
    for (int v = 0; v <= MAXV; v++) {
        while (cnt[v]--) {
            a[idx++] = v;
        }
    }
} 
```
:::
Nhận xét: Vòng lặp ngoài ta sẽ chạy từ $0$ đến $\max a_{i}$, vòng lặp trong in ra mỗi giá trị $\texttt{cnt}[i]$ lần, vậy tổng tất cả các lần in bằng $n$.

Độ phức tạp: $\mathcal{O}(n + \max a_{i})$.

__Nhược điểm__: Mảng không thể chứa các $a_{i}$ có giá trị âm hay quá lớn (vượt quá $10^{7}$).

![CountingSortScene (1)](https://hackmd.io/_uploads/ByMyefp0le.gif)

### Sắp xếp trộn (Merge Sort)

#### Ý tưởng

Sắp xếp trộn là một thuật toán dựa trên ý tưởng Chia để trị như sau:

* Để sắp xếp một dãy gồm $n$ phần tử, ta chia dãy thành hai nửa và dùng đệ quy sắp xếp từng nửa; ta chia để trị cho đến khi mỗi dãy con chỉ còn một phần tử.
* Khi gộp hai dãy con đã được sắp xếp, vị trí tương đối của các phần tử trong cùng một dãy con không còn quan trọng, ta chỉ cần xét các phần tử ở đầu mỗi dãy. Vì vậy, ta sử dụng hai con trỏ, mỗi con trỏ trỏ vào đầu một dãy con, so sánh hai phần tử đang trỏ tới, chọn phần tử nhỏ hơn đưa vào dãy mới, sau đó dịch con trỏ tương ứng, lặp lại cho đến khi hoàn tất.

Đối với các bài toán cần mô phỏng phép gộp giống như trong Merge Sort, bạn đọc có thể tham khảo hàm `merge` của C++ STL.

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
void mergeArray(vector<int> &a, int left, int mid, int right){
    vector<int> L(a.begin() + left, a.begin() + mid + 1);
    vector<int> R(a.begin() + mid + 1, a.begin() + right + 1);
    int i = 0, j = 0, k = left;

    while(i < L.size() && j < R.size()){
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }

    while(i < L.size()) a[k++] = L[i++];
    while(j < R.size()) a[k++] = R[j++];
}

void MergeSort(vector<int> &a, int left, int right){
    if(left >= right) return;

    int mid = (left + right) / 2;
    MergeSort(a, left, mid);
    MergeSort(a, mid + 1, right);
    mergeArray(a, left, mid, right);
}
```
:::
Nhận xét: Mỗi lần chia đôi có $\log n$ tầng chia để trị, ở mỗi tầng, tổng độ dài các dãy con là $n$.

Độ phức tạp: $\mathcal{O}(n \times \log n)$.

![MergeSortScene](https://hackmd.io/_uploads/BkscW-AAxe.gif)

### Sắp xếp vun đống (Heap Sort)

Trước khi đến với thuật toán này, bạn đọc nên tham khảo kiến thức cần có về Binary Heap tại <a href="https://wiki.vnoi.info/translate/wcipeg/Binary-Heap">đây</a>. Bạn đọc nên xem trước kiến thức trên vì trong bài viết mình sẽ không nói lại.

#### Giới thiệu: 
Heap Sort là thuật toán sắp xếp dựa trên cấu trúc dữ liệu heap - cụ thể là binary heap (cây nhị phân hoàn chỉnh)

#### Ý tưởng

Heap Sort hoạt động trên 2 giai đoạn chính:
1. Xây dựng 1 max-heap từ mảng ban đầu
    * Ta hoán đổi các phần tử sao cho các phần tử thỏa mãn tính chất của max-heap.
    * Sau bước này, phần tử lớn nhất của mảng sẽ nằm ở vị trí đầu tiên (root của heap).
    * Quá trình xây dựng mất $\mathcal{O}(n)$ .
2. Thực hiện sắp xếp
    * Hoán đổi phần tử ở đỉnh (lớn nhất) với phần tử cuối của heap.
    * Giảm kích thước của heap đi 1 (coi như phần tử cuối cùng đã được sắp xếp).
    * Lặp lại cho đến khi heap chỉ còn 1 phần tử.
    * Quá trình này ta sẽ mất $\mathcal{O}(n \times \log n)$.

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
// Hàm heapify để duy trì tính chất max-heap tại node i
void heapify(int a[], int n, int i){
    int largest = i;       // Giả sử node i là lớn nhất
    int left = 2 * i + 1;    // Con trái
    int right = 2 * i + 2;   // Con phải

    // Nếu con trái lớn hơn cha
    if(left < n && a[left] > a[largest])
        largest = left;

    // Nếu con phải lớn hơn cha (hoặc lớn hơn con trái)
    if(right < n && a[right] > a[largest])
        largest = right;

    // Nếu node lớn nhất không phải là node cha
    if(largest != i){
        swap(a[i], a[largest]);  // Hoán đổi
        heapify(a, n, largest);    // Gọi đệ quy
    }
}

void heapSort(int a[], int n){
    // Bước 1: Xây dựng max heap
    for(int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Bước 2: Trích từng phần tử lớn nhất ra cuối mảng
    for(int i = n-1; i >= 0; i--){
        swap(arr[0], arr[i]);   // Đưa max hiện tại ra cuối
        heapify(arr, i, 0);     // Duy trì heap cho phần còn lại
    }
}
```
:::
* Đánh giá thuật toán: Heap Sort có ý tưởng giống với Selection Sort, nhưng ở đây ta sẽ dùng heap thay vì duyệt, vì vậy độ phức tạp sẽ được tối ưu.
* Độ phức tạp: $\mathcal{O}(n \times \log n)$.
### Sắp xếp nhanh (Quick Sort)
Quicksort là một trong những thuật toán sắp xếp hiệu quả nhất và được sử dụng rộng rãi trong nhiều thư viện lập trình hiện nay. Thuật toán hoạt động theo tư tưởng chia để trị:

Trước hết, ta chọn một phần tử làm $\texttt{pivot}$, sau đó phân hoạch mảng sao cho mọi phần tử nhỏ hơn $\texttt{pivot}$ nằm ở bên trái, và mọi phần tử lớn hơn $\texttt{pivot}$ nằm ở bên phải. Khi mảng đã được chia thành hai phần độc lập, ta tiếp tục đệ quy sắp xếp từng phần con.

Điểm quan trọng nhất của Quicksort nằm ở việc chọn $\texttt{pivot}$ sao cho hai phần sau khi phân hoạch có kích thước tương đối cân bằng. Khi đó, cây đệ quy gần như là cây nhị phân cân bằng, giúp thuật toán đạt được hiệu năng tối ưu.
#### Phân hoạch Lomuto
* Chọn phần tử cuối cùng trong mảng làm $\texttt{pivot}$.
* Dùng hai con trỏ: 
    - $i$ để đánh dấu vùng chứa các phần tử $\le$ $\texttt{pivot}$
    - $j$ duyệt từ $p$ tới $r - 1$.
* Khi $a_{j}$ $\le$ $\texttt{pivot}$, ta tăng $i$ và hoán đổi $a_{i}$ và $a_{j}$.
* Cuối cùng hoán đổi $a_{i+1}$ với $a_{r}$.
* Trả về chỉ số $i+1$ làm vị trí $\texttt{pivot}$.

:::spoiler Code tham khảo
```cpp=
int vi_tri(int l, int r){
    int pivot = a[r];
    int i = l - 1;
    for(int j = l; j < r; j++){
        if(a[j] <= pivot){
            i++;
            swap(a[i], a[j]);
        }
    }
    i++;
    swap(a[i], a[r]);
    return i;
}

void quicksort(int l, int r){
    if(l >= r) return;
    int pos = vi_tri(l, r);
    quicksort(l, pos);
    quicksort(pos + 1, r);
}
```
:::
![QuickSortLomuto](https://hackmd.io/_uploads/rJ-a-W0Cxx.gif)

#### Phân hoạch Hoare

Phương pháp này được Tony Hoare phát triển cùng với khái niệm Quicksort ban đầu:
* Chọn 1 $\texttt{pivot}$ (thường là phần tử đầu).
* Dùng hai con trỏ $i$ (bắt đầu từ trái) và $j$ (bắt đầu từ phải).
* Di chuyển $i$ sang bên phải cho đến khi $a_{i}$ $\ge$ $\texttt{pivot}$.
* Di chuyển $j$ sang bên trái cho đến khi $a_{j}$ $\le$ $\texttt{pivot}$.
* Nếu $i$ $\lt$ $j$, hoán đổi $a_{i}$ và $a_{j}$.
* Khi $i$ $\ge$ $j$, dừng và trả về $i$ (hoặc $j$) làm $\texttt{pivot}$.
* Tiếp tục đệ quy 2 phần $[p; j]$ và $[j + 1; r]$.

:::spoiler Code tham khảo
```cpp=
int vi_tri2(int l, int r){
    int pivot = a[l];
    int i = l - 1, j = r + 1;
    while(true){
        do{
            i++;
        }while(a[i] < pivot);
        do{
            j--;
        }while(a[j] > pivot);
        if(i < j){
            swap(a[i], a[j]);
        }
        else return j;
    }
}

void quicksort(int l, int r){
    if(l >= r) return;
    int pos = vi_tri2(l, r);
    quicksort(l, pos);
    quicksort(pos + 1, r);
}
```
:::
Độ phức tạp: $\mathcal{O}(n \times \log n)$

![QuickSortHoare](https://hackmd.io/_uploads/S1vCbZCRex.gif)

Nhược điểm: Qua 2 ví dụ minh họa trên, ta thấy trong trường hợp tệ nhất, Quick Sort có thể chạy lên tới $\mathcal{O}(n^2)$.

### Sắp xếp cơ số (Radix Sort)
Radix Sort không sắp xếp bằng cách so sánh trực tiếp các phần tử, mà sắp xếp theo từng chữ số trong một hệ cơ số $d$. Với hệ cơ số $d$, mỗi số có tối đa $\log_d \max$ chữ số.

Ở mỗi lượt, Radix Sort sắp xếp mảng theo một chữ số, bắt đầu từ chữ số thấp nhất (hàng đơn vị) đến chữ số cao nhất. Việc sắp xếp được thực hiện bằng __Counting Sort__, vì các chữ số chỉ nằm trong khoảng $[0, d - 1]$.

Nhờ tính ổn định này, thứ tự các chữ số đã được sắp xếp ở các lượt trước được giữ nguyên, đảm bảo sau khi xử lý tất cả các chữ số, mảng đã được sắp xếp hoàn chỉnh.

Ví dụ, để sắp xếp dãy gồm các số $[193, 209, 45, 247, 109, 245, 49, 1]$ và hệ cơ số $d = 10$, Radix Sort thực hiện $3$ bước sắp xếp như sau:

- Sắp xếp các chữ số hàng đơn vị:
$$
[00\underline{1}, 19\underline{3}, 04\underline{5}, 24\underline{5}, 24\underline{7}, 20\underline{9}, 10\underline{9}, 04\underline{9}]
$$

- Sau đó, ta sắp xếp các chữ số hàng chục:
$$
[0\underline{0}1, 2\underline{0}9, 1\underline{0}9, 0\underline{4}5, 2\underline{4}5, 2\underline{4}7, 0\underline{4}9, 1\underline{9}3]
$$

- Cuối cùng, ta sắp xếp các chữ số hàng trăm:
$$
[\underline{0}01, \underline{0}45, \underline{0}49, \underline{1}09, \underline{1}93, \underline{2}09, \underline{2}45, \underline{2}47]
$$

#### Cài đặt

:::spoiler Code tham khảo
```cpp=
void countingSortByDigit(vector<int>& a, int exp){
    int n = a.size();
    vector<int> v(n);
    vector<int> dem(10, 0);

    // Đếm số lượng xuất hiện của mỗi chữ số
    for(int i = 0; i < n; i++){
        int digit = (a[i] / exp) % 10;
        dem[digit]++;
    }
    for(int i = 1; i < 10; i++){
        dem[i] += dem[i - 1];
    }
    for(int i = n - 1; i >= 0; i--){
        int digit = (a[i] / exp) % 10;
        v[dem[digit] - 1] = a[i];
        dem[digit]--;
    }
    for(int i = 0; i < n; i++){
        a[i] = v[i];
    }
}

void radixSort(vector<int>& a){
    // Tìm số lớn nhất để biết số chữ số
    int mx = *max_element(a.begin(), a.end());
    for(int exp = 1; mx / exp > 0; exp *= 10){
        countingSortByDigit(a, exp);
    }
}
```
:::
Độ phức tạp: $\mathcal{O}(n \times k)$ với $k$ là số chữ số của số lớn nhất.

## So sánh các thuật toán sắp xếp

| **Thuật toán** | **Độ phức tạp** (Tốt / Trung bình / Xấu) | **Bộ nhớ phụ** | **Tính ổn định** | **Cách sắp xếp** | **Ưu điểm** | **Nhược điểm** |
|-----------------|-----------------------------------------|----------------|-----------------|-----------------|-------------|----------------|
| **Selection Sort** *(Sắp xếp chọn)* | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | Không ổn định | So sánh, đổi chỗ | Dễ cài đặt, ít hoán đổi | Hiệu năng kém với dữ liệu lớn |
| **Bubble Sort** *(Sắp xếp nổi bọt)* | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | Ổn định | So sánh–đổi chỗ | Dễ hiểu, nhận biết nhanh dữ liệu gần sắp xếp | Rất chậm với mảng lớn |
| **Insertion Sort** *(Sắp xếp chèn)* | $\mathcal{O}(n)$ / $\mathcal{O}(n^2)$ / $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | Ổn định | So sánh, chèn | Hiệu quả với mảng nhỏ hoặc gần sắp xếp | Kém hiệu quả với dữ liệu ngẫu nhiên |
| **Counting Sort** *(Sắp xếp đếm/phân phối)* | $\mathcal{O}(n + k)$ | $\mathcal{O}(n + k)$ | Ổn định | Không so sánh | Rất nhanh với giá trị nhỏ, nguyên dương | Giới hạn phạm vi giá trị, tốn bộ nhớ |
| **Radix Sort** *(Sắp xếp cơ số)* | $\mathcal{O}(d\times(n + k))$ | $\mathcal{O}(n + k)$ | Ổn định | Không so sánh | Nhanh với số nguyên có độ dài chữ số cố định | Khó áp dụng cho dữ liệu không phải số hoặc độ dài khác nhau |
| **Merge Sort** *(Sắp xếp trộn)* | $\mathcal{O}(n \times \log n)$ | $\mathcal{O}(n)$ | Ổn định | Chia để trị | Độ phức tạp ổn định, thích hợp dữ liệu lớn | Tốn bộ nhớ phụ |
| **Heap Sort** *(Sắp xếp vun đống)* | $\mathcal{O}(n \times \log n)$ | $\mathcal{O}(1)$ | Không ổn định | So sánh–đổi chỗ | Không cần bộ nhớ phụ | Khó cài đặt, không ổn định |
| **Quick Sort** *(Sắp xếp nhanh)* | $\mathcal{O} (n \times \log n)$ / $\mathcal{O} (n \times \log n)$ / $\mathcal{O}(n^2)$ | $\mathcal{O}(\log n)$ | Không ổn định | Chia để trị | Trung bình rất nhanh, sử dụng phổ biến | Dễ bị $\mathcal{O}(n^2)$ nếu chọn pivot kém |

Ở phần giới thiệu ta có nhắc đến hàm sort trong C++ (IntroSort). Về cơ bản, IntroSort chạy dựa trên QuickSort vì thuật toán này nhanh trong hầu hết các trường hợp. Khi phát hiện nguy cơ chậm và có thể rơi vào $\mathcal{O}(n^2)$, nó sẽ chuyển sang dùng HeapSort để đảm bảo hiệu năng. Với các mảng nhỏ, thuật toán dùng thêm InsertionSort cho gọn và nhanh hơn. Nói ngắn gọn, đây là một thuật toán kết hợp nhiều thuật toán sắp xếp khác nhau tùy từng tình huống.
## Xây dựng comparator cho hàm sort

Trong lập trình, hầu hết các ngôn ngữ đều cung cấp hàm sắp xếp để sắp xếp các phần tử trong một dãy theo thứ tự tăng dần hoặc giảm dần.

Tuy nhiên, trong thực tế, không phải lúc nào chúng ta cũng chỉ cần sắp xếp theo giá trị thông thường.
Đôi khi, bài toán yêu cầu sắp xếp theo một tiêu chí đặc biệt — ví dụ như:
* Sắp xếp theo giá trị tuyệt đối.
* Sắp xếp học sinh theo chiều cao và cân nặng.
* Sắp xếp một cách tùy chỉnh mà không phải tăng dần hay giảm dần đơn thuần.

Để làm được điều này, ta cần truyền thêm 1 comparator (hàm so sánh tùy chỉnh) vào hàm sort.

### Định nghĩa
Comparator là một hàm (hoặc biểu thức lambda) dùng để xác định quy tắc so sánh giữa 2 phần tử trong quá trình sắp xếp.
Cụ thể, comparator sẽ nhận vào 2 phần tử $a$ và $b$, và trả về:
* $\texttt{true}$ nếu $a$ đứng trước $b$ (theo thứ tự mong muốn).
* $\texttt{false}$ nếu $a$ đứng sau $b$.

Nói cách khác, comparator giúp ta nói với hàm sort tiêu chí nào "nhỏ hơn" theo ý của riêng mình.

### Ví dụ 1: Sắp xếp theo giá trị tuyệt đối
Giả sử ta có mảng:
```cpp=
vector<int> a = {-3, 7, -1, 4, 2};
```
Nếu sắp xếp bình thường, kết quả sẽ là:
```cpp=
-3, -2, -1, 4, 7
```
Ta cần tự định nghĩa comparator như sau:
```cpp=
bool cmp(int a, int b){
    if (abs(a) != abs(b))
        return abs(a) < abs(b);
    return a < b; // phân biệt 2 và -2
}

```
Sau đó truyền vào hàm sort:
```cpp=
sort(a.begin(), a.end(), cmp);
```
Kết quả là:
```cpp=
-1, -2, -3, 4, 7
```
### Ví dụ 2: Sắp xếp theo nhiều tiêu chí khác nhau
Giả sử ta có danh sách học sinh, mỗi học sinh có 2 thông tin: chiều cao và cân nặng.
```cpp=
struct Student{
    int height;
    int weight;
};
```
Danh sách ban đầu:
```cpp=
vector<Student> students = {
    {170, 60},
    {165, 55},
    {170, 50},
    {160, 45}
}
```
Yêu cầu:
* Sắp xếp tăng dần theo chiều cao.
* Nếu 2 học sinh có cùng chiều cao, sắp xếp tăng dần theo cân nặng.
Khi đó comparator sẽ được viết như sau:
```cpp=
bool cmp(const Student &a, const Student &b){
    if(a.height == b.height)
        return a.weight < b.weight;
    return a.height < b.height;
}
```

### Mẹo và lưu ý
1. Comparator phải tuân thủ tính chất bắc cầu:
    Nếu $\texttt{cmp}(a, b)$ và $\texttt{cmp}(b, c)$ đều đúng thì $\texttt{cmp}(a, c)$ cũng phải đúng.
    Nếu không, hàm sort có thể cho kết quả không xác định.
2. Không nên viết comparator có logic mâu thuẫn.
3. Có thể dùng lambda expression gọn hơn như sau:
```cpp=
sort(students.begin(), students.end(), [](const Student &a, const Student &b){
    if(a.height == b.height)
        return a.weight < b.weight;
    return a.height < b.height;
});
```
### Đánh giá
* Comparator giúp ta kiểm soát cách sắp xếp dữ liệu theo tiêu chí riêng.
* Có thể áp dụng cho mọi kiểu dữ liệu: số, chuỗi, cấu trúc, đối tượng...
* Đây là kĩ năng rất quan trọng khi giải các bài toán sắp xếp phức tạp trong thực tế hay lập trình thi đấu.
## Bài tập áp dụng

### <a href="https://codeforces.com/contest/1681/problem/C" target="_blank">Double Sort</a>

Bạn được cho 2 mảng số nguyên cùng độ dài $n$: 
$a = [a_1, a_2, \ldots, a_n]$ và $b = [b_1, b_2, \ldots, b_n]$. 

Trong 1 thao tác, bạn được phép hoán đổi vị trí $i$ và $j$ (hoán đổi cả 2 mảng cùng lúc): $\texttt{swap}(a_i, a_j)$, $\texttt{swap}(b_i, b_j)$.

Mục tiêu biến 2 mảng $a$ và $b$ thành 2 dãy không giảm. Nếu có thể, in ra danh sách hoán đổi, ngược lại in ra $-1$.

<details>
<summary>Lời giải</summary>

Ta nhận xét rằng trong trạng thái cuối cùng, các cặp $(a_i, b_i)$ phải được sắp xếp theo một thứ tự tăng đồng thời - nghĩa là nếu một cặp đứng trước, thì cả 2 phần đều không lớn hơn phần sau.

Do đó, ta có mảng chỉ số $tmp = [0, 1,..., n - 1]$ và nó sắp xếp theo cặp $(a_i, b_i)$.

Nếu sau khi sắp xếp, vẫn tồn tại $a_{\texttt{tmp}[i]}$ $\gt$ $a_{\texttt{tmp}[i + 1]}$ hoặc $b_{\texttt{tmp}[i]}$ $\gt$ $b_{\texttt{tmp}[i + 1]}$ thì việc sắp xếp đồng thời là **không thể xảy ra**.

Ngược lại, nếu điều kiện trên thỏa mãn, ta có thể dùng thuật toán sắp xếp (ở đây sẽ dùng bubble sort) để ghi nhận các phép hoán vị.

</details>

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n; cin >> n;
        vector<int> a(n), b(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++) cin >> b[i];

        vector<int> tmp(n);
        iota(tmp.begin(), tmp.end(), 0);

        sort(tmp.begin(), tmp.end(), [&](int i, int j) {
            if (a[i] == a[j]) return b[i] < b[j];
            return a[i] < a[j];
        });

        bool ok = true;
        for (int i = 0; i + 1 < n; i++) {
            if (a[tmp[i]] > a[tmp[i + 1]] || b[tmp[i]] > b[tmp[i + 1]]) {
                cout << -1 << "\n";
                ok = false;
                break;
            }
        }
        if (!ok) continue;

        vector<pair<int,int>> ans;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1; j++) {
                if (a[j] > a[j + 1] || b[j] > b[j + 1]) {
                    swap(a[j], a[j + 1]);
                    swap(b[j], b[j + 1]);
                    ans.push_back({j + 1, j + 2});
                }
            }
        }

        cout << ans.size() << "\n";
        for (auto [x, y] : ans)
            cout << x << " " << y << "\n";
    }
    return 0;
}
```
:::

### <a href="https://drive.google.com/file/d/1Sjx7hIb6hlSVp0b0Zs9AoIPhXeAO9egq/view?usp=sharing" target="_blank">Counting Inversion</a>

<details>
<summary>Lời giải</summary>

Bài toán cho một dãy số gồm $n$ phần tử và yêu cầu đếm số lần hoán đổi khi sắp xếp dãy theo thứ tự không giảm bằng thuật toán Bubble Sort đã cho.
    
Nếu mô phỏng trực tiếp Bubble Sort thì độ phức tạp là $\mathcal{O}(n^2)$, không đủ nhanh với $n$ $\le$ $2 \cdot 10^5$.
    
Để đếm số nghịch thế, ta sử dụng Merge Sort kết hợp đếm nghịch thế trong quá trình trộn hai dãy con đã được sắp xếp.
    
Giả sử: Nửa trái đã được sắp xếp và nửa phải đã được sắp xếp.

Khi trộn: Nếu $a_i$ $\le$ $a_j$ suy ra không có nghịch thế. Nếu $a_i$ $\gt$ $a_j$, vì nửa trái đã được sắp xếp, nên tất cả các phần tử từ $i$ đến cuối nửa trái đều lớn hơn $a_j$.
    
Số nghịch thế được cộng thêm là: $(mid - i + 1)$

Độ phức tạp: $\mathcal{O}(n \log n)$

</details>

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>

using namespace std;

long long cnt = 0;
vector<long long> a, tmp;

void merge_sort(int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);

    int i = l, j = mid + 1, k = l;
    while(i <= mid && j <= r){
        if(a[i] <= a[j]){
            tmp[k++] = a[i++];
        } 
        else{
            tmp[k++] = a[j++];
            cnt += (mid - i + 1); // đếm nghịch thế
        }
    }
    while(i <= mid) tmp[k++] = a[i++];
    while(j <= r) tmp[k++] = a[j++];
    for (int p = l; p <= r; p++) a[p] = tmp[p];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    a.resize(n);
    tmp.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    merge_sort(0, n - 1);
    cout << cnt;
    return 0;
}
```
:::
### Bài tập làm thêm
https://codeforces.com/problemset?tags=sortings,1200-1500

### Tài liệu tham khảo
https://usaco.guide/silver/sorting-custom?lang=cpp