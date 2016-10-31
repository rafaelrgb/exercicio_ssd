#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Simulação do sistema dinânico

    // Valores de parametros e variaveis
    int a1 = 3, a2 = 2, b1 = 2, n = 0;
    double dt = 0.01, tf = 10.0, t = 0.0, y = 0.0, y1p = 0.0, y2p = 0.0;
    QVector<double> vy(1001), vt(1001);

    while ( t < tf )                                    // Loop de repetição
    {
        double u = 1.0;                                 // Entrada de excitação do sistema: degrau unitário
        y2p = (-1 * a1 * y1p) - (a2 * y) + (b1 * u);    // Valor da derivada de maior ordem
        y1p = y1p + y2p * dt;                           // Integração da variável y2p
        y = y + y1p * dt;
        t = t + dt;                                     // Incremento da variável independente
        n = n + 1;                                      // Incremento da variável de indexação
        vy[n] = y;                                      // Armazena valor da variável y em um vetor
        vt[n] = t;                                      // Armazena valor da variável t em um vetor
    }

    // Traçar gráfico da simulação de y(t)
    QCustomPlot* customPlot = ui->customPlot;

    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(vt, vy);
    // give the axes some labels:
    customPlot->xAxis->setLabel("t");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 12);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
