DROP DATABASE QuanLyBanHang;
CREATE DATABASE QuanLyBanHang;
USE QuanLyBanHang;

CREATE TABLE Customer (
	cID INT AUTO_INCREMENT PRIMARY KEY, -- Mã khách hàng (Khóa chính)
	cName VARCHAR(100) NOT NULL,        -- Tên khách hàng
	cAge INT                            -- Tuổi khách hàng
);

CREATE TABLE `Order` (
    oID INT AUTO_INCREMENT PRIMARY KEY, -- Mã hóa đơn (Khóa chính)
    cID INT NOT NULL,                   -- Mã khách hàng (Khóa ngoại)
    oDate DATE NOT NULL,                -- Ngày mua hàng
    oTotalPrice DECIMAL(10, 2),         -- Tổng giá trị hóa đơn
    FOREIGN KEY (cID) REFERENCES Customer(cID) -- Ràng buộc khóa ngoại
);

CREATE TABLE Product (
    pID INT AUTO_INCREMENT PRIMARY KEY, -- Mã sản phẩm (Khóa chính)
    pName VARCHAR(100) NOT NULL,        -- Tên sản phẩm
    pPrice DECIMAL(10, 2) NOT NULL      -- Giá sản phẩm
);

CREATE TABLE OrderDetail (
    oID INT NOT NULL,                   -- Mã hóa đơn (Khóa ngoại)
    pID INT NOT NULL,                   -- Mã sản phẩm (Khóa ngoại)
    odQTY INT NOT NULL,                 -- Số lượng sản phẩm
    PRIMARY KEY (oID, pID),             -- Khóa chính kết hợp
    FOREIGN KEY (oID) REFERENCES `Order`(oID),  -- Ràng buộc khóa ngoại tới bảng Order
    FOREIGN KEY (pID) REFERENCES Product(pID)   -- Ràng buộc khóa ngoại tới bảng Product
);

SHOW TABLES;


