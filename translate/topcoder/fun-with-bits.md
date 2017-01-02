# Fun with Bits
Bài viết bởi [bmerry](https://www.topcoder.com/members/bmerry).

Nguồn: [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/a-bit-of-fun-fun-with-bits/)

[[_TOC_]]

# Giới thiệu 

Hầu hết các kĩ thuật tối ưu dùng trong các kì thi Topcoder đều là những kĩ thuật cao cấp, có nghĩa là, các kĩ thuật này tối ưu trực tiếp thuật toán hơn là tối ưu cách cài đặt. Tuy nhiên, có một kĩ thuật tối ưu cơ bản nhưng sử dụng rất hiệu quả là thao tác bit (bit manipulation), hay sử dụng những bit thuộc biểu diễn của một số nguyên để biểu diễn một tập hợp. Nó không chỉ làm tăng tốc độ chạy, giảm dung lượng bộ nhớ, mà còn làm code chúng ta trở nên đơn giản hơn.

Mình sẽ bắt đầu bằng việc nhắc lại một số kiến thức cơ bản về bit, trước khi nghiên cứu những kĩ thuật sâu hơn. 

# Cơ bản 

Những thứ quan trọng nhất trong thao tác bit là những toán tử trên bit (bit-wise operator): `&` (and), `|` (or), `~` (not) và `^` (xor). Chắc hẳn các bạn đã quá quen với ba toán tử đầu tiên trong các phép toán logic (`&&`, `||`, và `!`). Dưới đây là bảng chân trị (truth tables): 

<table>
<tr>
<th>A</th>
<th>B</th>
<th>!A</th>
<th>A && B</th>
<th>A || B</th>
<th>A ^ B</th>
</tr>
<tr>
<td>0</td>
<td>0</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>0</td>
</tr>
<tr>
<td>0</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>1</td>
<td>1</td>
</tr>
<tr>
<td>1</td>
<td>0</td>
<td>0</td>
<td>0</td>
<td>1</td>
<td>1</td>
</tr>
<tr>
<td>1</td>
<td>1</td>
<td>0</td>
<td>1</td>
<td>1</td>
<td>0</td>
</tr>
</table>

Toán tử bit trên số nguyên cũng thực hiên giống vậy, chỉ khác một thứ là thay vì chuyển các tham số về true hoặc false, thì các toán tử bit được thực hiện trên các bit của các tham số. Do đó, nếu `A` là `1010` và `B` là `1100`, thì 
```
A & B = 1000$
A | B = 1110
A ^ B = 0110
~A = 11110101 (số chữ số 1 phụ thuộc vào kiểu dữ liệu của A)
```

Hai toán tử mà chúng ta cần phải biết nữa đó là toán tử dịch bit `a << b` và `a >> b`. Toán tử đầu tiên là dịch tất cả các bit của a sang trái b vị trí; Toán tử thứ hai cũng giống vậy nhưng dịch sang phải. Với những giá trị không âm (cũng là những số duy nhất mà ta sẽ xét đến), những bit mới xuất hiện (do dịch trái) sẽ bằng 0. Dịch trái (left-shifting) $b$ bit đồng nghĩa với việc nhân với $2^{b}$ và dịch phải (right-shifting) đồng nghĩa với chia nguyên cho $2^{b}$. Dịch bit được sử dụng nhiều nhất để truy cập vào một bit bất kì, ví dụ, `1 << x` là một số nhị phân với bit thứ x bằng 1 và các bit khác bằng 0 (bit luôn luôn được đếm từ bên phải (least-significant), đếm bắt đầu từ 0). 