// include/MainWindow.hpp
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void numericButtonClicked();
    void okButtonClicked();
    void cancelButtonClicked();
    void cashButtonClicked();
    void cardButtonClicked();
    void receiptButtonClicked();

private:
    void createKeypad();
    void createFunctionButtons();
    void setupLayout();
    void styleComponents();

    QWidget *centralWidget;
    QLabel *displayPanel;
    QVector<QPushButton *> numericButtons;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *cashButton;
    QPushButton *cardButton;
    QPushButton *receiptButton;
};

#endif // MAINWINDOW_HPP