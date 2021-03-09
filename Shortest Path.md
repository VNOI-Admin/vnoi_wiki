# **Các thuật về tìm đường đi ngắn nhất**

[[_TOC_]]

Như các bạn đã biết đường đi ngắn nhất là một trong những chủ đề quan trọng nhất chi nhưng thí sinh tìm kiếm xuất tuyển thẳng vào đại học.Ở bài viết này mình sẽ giới thiệu 3 thuật toán cơ bản của dạng bài tìm đường đi ngắn nhất.Dưới đây sẽ là 3 thuật toán mình sẽ giới thiệu.
* Thuật toán $Ford – Bellman$
* Thuật toán $Dijkstra$
* Thuật toán $Floyd$

# 1. Thuật toán $Ford – Bellman$
## Bài toán.
Cho đồ thị vô hướng có trọng số , **trọng số có thể âm**. Đồ thị có $n$ đỉnh và $m$ cạnh ,cho 2 đỉnh $s$ và đỉnh $t$.Yêu cầu tìm đường đi ngắn nhất từ $s$ đến $t$.

Giới hạn bài toán : $n \le 1000 , m \le 10000$.

Thuật toán $Ford – Bellman$ khác các thuật toán còn lại ở chỗ là nó có thể xử lí được cả đồ thị có trọng số âm, nó có thể tìm được chu trình âm - là một chu trình trong đó tổng trọng số các cạnh là số âm, chu trình này đặc biệt ở chỗ là nếu ta sửa dụng vô hạn lần chu tình này trên đường đi từ s đến t thì thì kết quả bài toán của chúng ta sẽ nhỏ đi vô hạn lần.
## Tư Tưởng thuật toán
Gọi d[v] là đường đi ngắn nhất từ s đến u. Ban đầu ta sẽ đặt tất cả các d[v] là giá trị lớn nhất mà khi tính mảng d[v] sẽ không bao giở dùng đến. Trong bài này mình sẽ đặt 2e9, d[s] = 0.

Gọi c[u,v] là trọng số cạnh đi từ u đến v.

Tư tưởng thuật toán như sau : 

* **Ta sẽ tối ưu dần các d[v] như sau** : 




    


