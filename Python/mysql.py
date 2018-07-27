import pymysql

db = pymysql.connect('localhost', 'root', '', 'test')

cursor = db.cursor()
sql = "select * from instructor"
cursor.execute(sql)
# data=cursor.fetchmany(5)
# print(data)
i = 0
while i < 5:
        print(cursor.fetchone())
        i = i + 1
