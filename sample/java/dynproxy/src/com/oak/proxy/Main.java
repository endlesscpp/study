package com.oak.proxy;

public class Main {
    public static void main(String[] args) {
        HelloService service = new HelloServiceImpl();
        HelloService proxy = (HelloService)ProxyBean.getProxyBean(
                service, new MyInterceptor());
        proxy.sayHello("World");
        System.out.println("name is null####");
        proxy.sayHello(null);
    }
}
