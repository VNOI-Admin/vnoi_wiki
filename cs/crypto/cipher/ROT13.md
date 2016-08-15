#ROT13

ROT13 ("rotate by 13 places") là một loại mã hóa thay thế chữ cái, bằng cách thay mỗi chữ cái bằng chữ thứ 13 sau nó trong bảng chữ cái. Đây là một trường hợp đặc biệt của Caesar Cipher, được phát minh từ thời Rome cổ.

Bởi vì bảng chữ cái Latin có 26 chữ cái, ROT13 là *inverse* của các chữ cái. Để giải mã, ta làm điều tương tự. Đây **không** phải là một thuật toán mã hóa tốt nhưng cũng đủ để mã hóa một bức thư ngắn.

##Cách sử dụng

Để sử dụng ROT13, ta chỉ cần thay chữ cái này bằng chữ cái thứ 13 sau nó trong bảng chữ cái. Để giải mã, chúng ta cũng thay bằng chữ cái thứ 13 sau nó là trở lại được về chữ ban đầu

![Alt](https://upload.wikimedia.org/wikipedia/commons/thumb/3/33/ROT13_table_with_example.svg/320px-ROT13_table_with_example.svg.png "ROT13")

Hay nói cách khác:
```
ROT13(ROT13(x)) = x
```
Ví dụ:
```
The Quick Brown Fox Jumps Over The Lazy Dog
Gur Dhvpx Oebja Sbk Whzcf Bire Gur Ynml Qbt
```

##Các biến thể

ROT5 cũng được sử dụng y hệt như ROT13 trong bảng chữ số (0 đến 9). 
Ngoài ra ROT13 và ROT5 còn được sử dụng trong cùng một văn bản.
Mở rộng ROT13, ta còn có ROT47. ROT47 áp dụng đối với chữ cái trong bảng mã ASCII. Ví dụ:
```
The Quick Brown Fox Jumps Over The Lazy Dog.
%96 "F:4< qC@H? u@I yF>AD ~G6C %96 {2KJ s@8]
```