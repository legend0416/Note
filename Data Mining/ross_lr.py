import numpy as np
import pandas as pd
from sklearn import linear_model

train = pd.read_csv("train.csv")
test = pd.read_csv("test.csv")
#remove open == 0
train = train[train.Open!=0]
data = np.asarray(train[["Store","Promo","StateHoliday","Sales"]])
for row in data:
    if row[2] == '0':
        row[2] = 0
    if row[2] == 'a':
        row[2] = 1
    if row[2] == 'b':
        row[2] = 2
    if row[2] == 'c':
        row[2] = 3

tables = {}
for row in data:
    if row[0] not in tables:
        tables[row[0]] = np.array([row[1:]])
    else:
        tables[row[0]] = np.append(tables[row[0]], np.array([row[1:]]), axis=0)
table_coef = {}
table_intercept = {}
for key, table in tables.iteritems():
    x, y = table[:,0:2], table[:,2]
    regr = linear_model.LinearRegression()
    regr.fit(x,y)
    table_coef[key] = regr.coef_
    table_intercept[key] = regr.intercept_
#print table_intercept

test_data = np.asarray(test[["Open","Store","Promo","StateHoliday"]])
#remove nans
for row in test_data:
    if np.isnan(row[0]):
        row[0] = 1
for row in test_data:
    if row[3] == '0':
        row[3] = 0
    if row[3] == 'a':
        row[3] = 1
    if row[3] == 'b':
        row[3] = 2
    if row[3] == 'c':
        row[3] = 3
tdx = test_data[:,2:4]
pred = np.array([])
for idx in range(test_data.shape[0]):
    if test_data[idx][0] == 0:
        pred = np.append(pred, 0)
    else:
        s = sum(table_coef[test_data[idx][1]] * tdx[idx])
        pred = np.append(pred, s + table_intercept[test_data[idx][1]])
rul = pd.DataFrame(pred, index=range(1, len(pred) + 1),columns=['Sales'])
rul.to_csv("result.csv")
