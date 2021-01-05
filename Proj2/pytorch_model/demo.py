'''
Date: 2020-12-16 14:18:42
Author: Kang Wang
LastEditors: Kang Wang
LastEditTime: 2021-01-05 12:38:01
'''
#https://blog.csdn.net/weixin_44023658/article/details/106123841
import os
import argparse

import cv2
import numpy as np

import torch
import torchvision.transforms as T
print('PyTorch version: {}.'.format(torch.__version__))

from model import SimpleCLS
# init net
net = SimpleCLS(phase='test')
net = net.eval()
# print(net)
# load weight
state_dict = torch.load('./weights/face_binary_cls.pth',map_location=torch.device('cpu'))
net.load_state_dict(state_dict)


parser = argparse.ArgumentParser('Face binary classification')
#parser.add_argument('--img', default='samples/bg/03.jpg', type=str)
#args = parser.parse_args()
img = 'samples/bg.jpg'
img = cv2.imread(img)
img = T.ToTensor()(img).unsqueeze(0)
#print(net(T.ToTensor()(img).unsqueeze(0)))
with torch.no_grad():
    out = net(img)
    #(1,3,128,128)
    conf_score = out.squeeze(0)[1].data.numpy()
    #(2,1)
print('bg.jpg: '+'face score: {:.6f}.'.format(conf_score))
img = 'samples/face.jpg'
img = cv2.imread(img)
img = T.ToTensor()(img).unsqueeze(0)
#print(net(T.ToTensor()(img).unsqueeze(0)))
with torch.no_grad():
    out = net(img)
    #(1,3,128,128)
    conf_score = out.squeeze(0)[1].data.numpy()
    #(2,1)
print('face.jpg: '+'face score: {:.6f}.'.format(conf_score))
for i in range(10):
    img = 'samples/0'
    img = img+str(i)+'.jpg'
    img = cv2.imread(img)
    img = T.ToTensor()(img).unsqueeze(0)
    #print(net(T.ToTensor()(img).unsqueeze(0)))
    with torch.no_grad():
        out = net(img)
        #(1,3,128,128)
        conf_score = out.squeeze(0)[1].data.numpy()
        #(2,1)
    print('0'+str(i)+'.jpg: '+'face score: {:.6f}.'.format(conf_score))

