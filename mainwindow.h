#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *centralWidget;
    QHBoxLayout *mainLayout;

    QVBoxLayout *barMenu;
    QLabel *titleLabel;
    QVBoxLayout *statusLayout;

    QPushButton *btnDashboard;
    QPushButton *btnAuth;
    QPushButton *btnHistory;
    QPushButton *btnConnection;

    QWidget *statusWidget;
    QWidget *sidebarWidget;
    QWidget *dashboardWidget;
};
#endif // MAINWINDOW_H
