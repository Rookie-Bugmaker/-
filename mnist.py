# from tensorflow.python.keras.utils.np_utils import to_categorical
# from keras import models, layers, regularizers
# from keras.optimizers import RMSprop
# from keras.datasets import mnist
# import matplotlib.pyplot as plt
#
# # 加载数据集
# (train_images, train_labels), (test_images, test_labels) = mnist.load_data()
#
# train_images = train_images.reshape((60000, 28*28)).astype('float')
# test_images = test_images.reshape((10000, 28*28)).astype('float')
# train_labels = to_categorical(train_labels)
# test_labels = to_categorical(test_labels)
#
# network = models.Sequential()
# network.add(layers.Dense(units=128, activation='relu', input_shape=(28*28, ),))
# network.add(layers.Dense(units=32, activation='relu'))
# network.add(layers.Dense(units=10, activation='softmax'))
#
# # 编译步骤
# network.compile(optimizer=RMSprop(lr=0.001), loss='categorical_crossentropy', metrics=['accuracy'])
# # 训练网络，用fit函数, epochs表示训练多少个回合， batch_size表示每次训练给多大的数据
# network.fit(train_images, train_labels, epochs=10, batch_size=128, verbose=2)
#
# # 来在测试集上测试一下模型的性能吧
# # y_pre = network.predict(test_images[:5])
# # print(y_pre, test_labels[:5])
# test_loss, test_accuracy = network.evaluate(test_images, test_labels)
# print("test_loss:", test_loss, "    test_accuracy:", test_accuracy)


import numpy
numbers = 12
counter = 0
catgorys = 5
for i in range(1, 10000):
    b = numpy.ones((1, catgorys))
    a = numpy.random.randint(0, catgorys, (1, numbers))
    for k in range(0, numbers):
        b[0, int(a[0, k])] = 0
    if not(numpy.any(b)):
        counter += 1
print(counter)
