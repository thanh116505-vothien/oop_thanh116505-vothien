# Bài thực hành 01 - Quản lý bãi đỗ xe

## Đề bài
Xây dựng hệ thống quản lý bãi đỗ xe bằng C++ theo hướng đối tượng (OOP).

### Yêu cầu:
- 3 lớp: Xe, BaiDoXe, GiaoDien
- Ràng buộc: không dùng mảng (array/vector), không dùng con trỏ (pointer). Dùng các biến đơn lẻ và cờ bool để quản lý
- Tất cả thuộc tính để private, dùng getter/setter

### Các lớp:
1. Xe: mã xe, loại xe (Car, Motorcycle, Bicycle), giờ vào (0-23), thời gian đỗ, phí đỗ
2. BaiDoXe: mã bãi, kích thước (S: 1 xe, M: 2 xe, L: 3 xe), quản lý tối đa 3 xe
3. GiaoDien: quản lý tối đa 3 bãi đỗ, có menu console 9 chức năng

### Quy tắc tính phí:
- Đơn giá theo giờ: Car 6.000 VNĐ, Motorcycle 4.000 VNĐ, Bicycle 2.000 VNĐ
- Giờ cao điểm (6h-9h sáng, 15h-18h chiều): 2 giờ đầu tăng 30% (+30%)
- Giờ thấp điểm: 2 giờ đầu giảm 5% (-5%)
- Từ giờ thứ 3 trở đi giảm 10% (-10%)
