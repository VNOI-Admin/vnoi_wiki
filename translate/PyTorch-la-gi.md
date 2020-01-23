Xem Nguồn (notebook tương tác)
[https://github.com/duc0/vitech/blob/master/jupyter/pytorch-tutorials/ch1_tensor.ipynb](https://github.com/duc0/vitech/blob/master/jupyter/pytorch-tutorials/ch1_tensor.ipynb)

PyTorch là gì?
PyTorch là thư viện tính toán xây dựng trên nền tảng ngôn ngữ Python. PyTorch nhắm vào hai mục tiêu chính

Hỗ trợ tính toán khoa học, thay thế cho thư viện NumPy (một thư viện Python hỗ trợ tính toán khoa học trên mảng nhiều chiều) và hỗ trợ GPU
Trở thành một nền tảng Deep Learning linh hoạt và hiệu quả
PyTorch được phát triển bởi Facebook (https://pytorch.org/) và là một thư viện mã nguồn mở (https://github.com/pytorch/pytorch)

Giới thiệu
Tensor ^^^^^^^

Trong ngữ cảnh các thư viện tính toán, Tensor có thể hiểu như là mảng nhiều chiều (giống như ndarray của thư viện NumPy). Tensor là sự tổng quát hoá của vector (mảng 1 chiều), ma trận (mảng 2 chiều). Tensor của PyTorch có thêm một lợi thế là có hỗ trợ tính toán trên GPU để tăng tốc độ.

Cài đặt
Cài đặt anaconda sau đó chạy lệnh

conda install pytorch torchvision -c pytorch

Chạy jupyter notebook để mở notebook này tương tác

Các hỗ trợ cơ bản về Tensor nằm trong module torch

In [10]:
from __future__ import print_function
import torch
Định nghĩa một ma trận 5x3, chưa khởi tạo giá trị:

In [11]:
x = torch.empty(5, 3)
print(x)
tensor([[ 0.0000e+00, -2.0000e+00, -1.6168e-21],
        [ 2.8643e-42,  7.1801e+28,  2.5958e-06],
        [ 7.3983e+31,  2.7691e+20,  1.0645e+24],
        [ 5.5603e+31,  4.2964e+24,  1.5842e-10],
        [ 3.9831e-11,  1.6925e-41,  2.5031e-37]])
Định nghĩa một ma trận 5x3 được khởi tạo ngẫu nhiên:

In [ ]:
x = torch.rand(5, 3)
print(x)
Định nghĩa một ma trận 5x3 khởi tạo với giá trị 0, kiểu dữ liệu (dtype) là long:

In [ ]:
x = torch.zeros(5, 3, dtype=torch.long)
print(x)
Khởi tạo tensor trực tiếp từ số liệu:

In [ ]:
x = torch.tensor([5.5, 3])
print(x)
Khởi tạo tensor từ một tensor sẵn có. Các phương thức khởi tạo này sẽ dùng lại các thuộc tính của tensor đầu vào (như là dtype) trừ khi người dùng cung cấp giá trị mới cho các thuộc tính.

In [18]:
x = x.new_ones(5, 3, dtype=torch.double)      # new_* methods take in sizes
print(x)

x = torch.randn_like(x, dtype=torch.float)    # override dtype!
print(x)                                      # result has the same size
tensor([[1., 1., 1.],
        [1., 1., 1.],
        [1., 1., 1.],
        [1., 1., 1.],
        [1., 1., 1.]], dtype=torch.float64)
tensor([[-1.4884,  2.4420,  0.7131],
        [ 2.2873, -0.3993, -0.0366],
        [-1.8804, -0.4695,  0.4877],
        [ 0.1583,  0.4593,  0.1510],
        [-0.1133, -1.4087,  1.6926]])
Trả về kích thước của tensor (nghĩa là tất cả kích thước của các chiều của mảng):

In [13]:
print(x.size())
torch.Size([5, 3])
Ghi chú
``torch.Size`` là tuple trong Python nên sẽ hỗ trợ tất cả các phép tính thông dụng với tuple.

Phép toán ^^^^^^^^^^ Có nhiều cú pháp khác nhau để biểu diễn phép toán. Trong ví dụ sau ta sẽ xem xét phép toán cộng 2 tensor.

Phép cộng: cú pháp thứ nhất

In [20]:
x = torch.ones(2, 3)
y = 3 * torch.ones(2, 3)
print(x)
print(y)
print(x + y)
tensor([[1., 1., 1.],
        [1., 1., 1.]])
tensor([[3., 3., 3.],
        [3., 3., 3.]])
tensor([[4., 4., 4.],
        [4., 4., 4.]])
Phép cộng: cú pháp thứ hai

In [21]:
print(torch.add(x, y))
tensor([[4., 4., 4.],
        [4., 4., 4.]])
Phép cộng: chỉ định trước tensor đầu ra

In [22]:
result = torch.empty(5, 3)
torch.add(x, y, out=result)
print(result)
tensor([[4., 4., 4.],
        [4., 4., 4.]])
Phép cộng tại chỗ (lưu ý việc tiết kiệm bộ nhớ là khá quan trọng để tăng hiệu quả tính toán)

In [23]:
# Cộng x vào y
y.add_(x)
print(y)
tensor([[4., 4., 4.],
        [4., 4., 4.]])
Ghi chú
Các phép toán nào mà thay đổi giá trị của tensor tại chỗ thì sẽ có tên kết thúc bởi dấu ``_``. Ví dụ: ``x.copy_(y)``, ``x.t_()``, sẽ thay đổi giá trị của ``x``.

Bạn có thể tận dụng các cách truy cập theo chỉ số giống như NumPy! Ví dụ để in ra cột #1 của ma trận x:

In [25]:
print(x[:, 1])
tensor([1., 1.])
Thay đổi kích thước: nào muốn thay đổi kích thước Tensor, bạn có thể dùng torch.view:

In [28]:
x = torch.randn(4, 4)
y = x.view(16)
z = x.view(-1, 8)  # -1 nghĩa là là kích thước sẽ được suy ra từ các chiều còn lại
print(x.size(), y.size(), z.size())
torch.Size([4, 4]) torch.Size([16]) torch.Size([2, 8])
Tất nhiên khi dùng view, kích thước mới phải có số phần tử bằng số phần tử của Tensor. Ví dụ sau sẽ báo lỗi:

In [29]:
y = x.view(14)
---------------------------------------------------------------------------
RuntimeError                              Traceback (most recent call last)
<ipython-input-29-66e035dcc596> in <module>()
----> 1 y = x.view(14)

RuntimeError: invalid argument 2: size '[14]' is invalid for input with 16 elements at /Users/soumith/miniconda2/conda-bld/pytorch_1532623076075/work/aten/src/TH/THStorage.cpp:84
Nếu tensor chỉ có 1 phần tử thì có thể dùng .item() để truy cập giá trị duy nhất đó

In [30]:
x = torch.randn(1)
print(x)
print(x.item())
tensor([-0.0990])
-0.09897159039974213
Đọc thêm:

Hơn 100+ phép toán trên Tensor, bao gồm transposing, indexing, slicing, các phép tính toán học, đại số tuyến tính, số ngẫu nhiên, ..., được mô tả tại <http://pytorch.org/docs/torch>_.

Tương tác với NumPy
Chuyển đổi giữa PyTorch tensor và mảng NumPy rất dễ dàng.

PyTorch tensor và mảng NumPy cùng chia sẻ bộ nhớ dữ liệu, thay đổi bên này thì bên kia cũng thay đổi theo.

Chuyển từ Tensor về mảng NumPy ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In [31]:
a = torch.ones(5)
print(a)
tensor([1., 1., 1., 1., 1.])
In [32]:
b = a.numpy()
print(b)
[1. 1. 1. 1. 1.]
Thay đổi a thì b cũng thay đổi theo

In [33]:
a.add_(1)
print(a)
print(b)
tensor([2., 2., 2., 2., 2.])
[2. 2. 2. 2. 2.]
Chuyển từ mảng NumPy về Tensor ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Thay đổi a thì b cũng thay đổi theo

In [34]:
import numpy as np
a = np.ones(5)
b = torch.from_numpy(a)
np.add(a, 1, out=a)
print(a)
print(b)
[2. 2. 2. 2. 2.]
tensor([2., 2., 2., 2., 2.], dtype=torch.float64)
Tất cả các kiểu Tensor (trên CPU) ngoại trừ CharTensor đều hỗ trợ chuyển đổi với NumPy và ngược lại.

Tensors trên CUDA
(CUDA là nền tảng tính toán GPU của NVidia) Tensor có thể được chuyển đến thiết bị bất kỳ bằng cách gọi hàm .to .

In [35]:
# Chạy nếu như máy tính hỗ trợ CUDA (có GPU của NVidia)
# Dùng ``torch.device`` để đưa tensors ra/vào GPU
if torch.cuda.is_available():
    device = torch.device("cuda")          # a CUDA device object
    y = torch.ones_like(x, device=device)  # directly create a tensor on GPU
    x = x.to(device)                       # or just use strings ``.to("cuda")``
    z = x + y
    print(z)
    print(z.to("cpu", torch.double))       # ``.to`` can also change dtype together!