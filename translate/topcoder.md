# Luồng cực đại trên mạng - maxflow network

[[_TOC_]]

# 0. Kiến thức cần biết

# 1. Ứng dụng

# 2. Phát biểu bài toán

Cho một mạng có dạng một đồ thị vô hướng $$G=(E,V)$$ (V là tập đỉnh, E là tập cạnh) mỗi cạnh trên đồ thị như một kênh chuyển tải nước giữa 2 đỉnh riêng biệt trong đồ thị và có sức chứa là c. Trong mạng lưới có một đỉnh phát x và một đỉnh thu y
<Yêu cầu>: với mỗi kênh truyền tải (e thuộc E) cần xác định giá trị $$fe (fe <= ce)$$ tương ứng được gọi là giá trị dòng chảy (flow) sao cho với mỗi đỉnh $$u thuộc tập V/{s,t}$$ tổng $$f(V,u)=f(u,V)$$ (tổng giá trị dòng chảy đi vào u bằng tổng giá trị dòng chảy đi ra). Hơn thế nữa ta cần tìm các giá trị f sao Tổng f(x,V) là lớn nhất.


# 3. cách giải bài toán

## 3.1 mạng thặng dư - residual network

## 3.2 đường tăng luồng - augment path

## 3.3 ví dụ

## 3.4 thuật toán

## 3.5 tính đúng dắn

### 3.5.1 lát cắt s-t

### 3.5.1 lát cắt s-t hẹp nhất

### 3.5.2 chứng minh

## 3.6 Các thuật toán tìm đường mở

# 4. Bài toán liên quan