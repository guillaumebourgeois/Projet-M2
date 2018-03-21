/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#include "Deck_builder.h"

using namespace std;

Deck_builder::Deck_builder(QWidget *parent)
	: QMainWindow(parent)
{
	QString url = R"(C:\Users\guill\Desktop\cards\439376.jpg)";
	QPixmap img(url);

	int i, j, k;

	ui.setupUi(this);

	// Buttons
	connect(this->ui.openButton, SIGNAL(clicked()), this, SLOT(handleOpenButton()));
	connect(this->ui.saveButton, SIGNAL(released()), this, SLOT(handleSaveButton()));

	// Vectors of labels
	this->proposals.resize(NB_PROPOSALS);
	this->deck.resize(DECKSIZE);
	this->buttons.resize(NB_PROPOSALS);

	// Initiate proposals box, scroll area, widget, labels
	ui.proposalsBox->setFixedHeight(465);
	ui.proposalsBox->setFixedWidth(1920);
	ui.proposalsBox->move(QPoint(0, 0));

	ui.proposalsArea->setFixedHeight(415);
	ui.proposalsArea->setFixedWidth(1920);
	ui.proposalsArea->move(QPoint(0, 50));

	QWidget *proposalsWidget = new QWidget();
	proposalsWidget->setFixedHeight(390);
	proposalsWidget->setFixedWidth(NB_PROPOSALS * (25 + WIDTHLABEL) + 25);
	ui.proposalsArea->setWidget(proposalsWidget);

	QGridLayout *layout = new QGridLayout;

	for (i = 0; i < NB_PROPOSALS; ++i)
	{
		this->proposals[i] = new QLabel("proposalsLabel" + i, proposalsWidget);
		this->proposals[i]->setFixedWidth(WIDTHLABEL);
		this->proposals[i]->setFixedHeight(HEIGHTLABEL);
		this->proposals[i]->move(QPoint(25 + i * (25 + WIDTHLABEL), 25));

		this->proposals[i]->setPixmap(img.scaled(QSize(WIDTHLABEL, HEIGHTLABEL), Qt::IgnoreAspectRatio));
	
		//this->proposals[i]->clear();
		this->buttons[i] = new QPushButton("" + i, proposalsWidget);
		this->buttons[i]->setFixedWidth(WIDTHLABEL);
		this->buttons[i]->setFixedHeight(40);
		this->buttons[i]->setStyleSheet("font: 14pt;");
		this->buttons[i]->setText("Poids");
		this->buttons[i]->move(QPoint(25 + i * (25 + WIDTHLABEL), 25 + HEIGHTLABEL + 10));

		connect(this->buttons[i], SIGNAL(released()), this, SLOT(handleAddButton(/*this*/)));
		
		//ui.proposalsBox
	}

	// Initiate deck box, scroll area, widget, labels
	ui.deckBox->setFixedHeight(689);
	ui.deckBox->setFixedWidth(1920);
	ui.deckBox->move(QPoint(0, 465));

	ui.deckArea->setFixedHeight(539);
	ui.deckArea->setFixedWidth(1920);
	ui.deckArea->move(QPoint(0, 50));

	QWidget *deckWidget = new QWidget();
	deckWidget->setFixedWidth(1920);
	deckWidget->setFixedHeight((DECKSIZE/5) * (25 + HEIGHTLABEL) + 25);
	ui.deckArea->setWidget(deckWidget);

	for (k = 0, i = 0; i < DECKSIZE; ++k)
	{
		for (j = 0; j < 7 && i < this->deck.size(); ++j, ++i)
		{
			this->deck[i] = new QLabel("deckLabel", deckWidget);
			this->deck[i]->setFixedWidth(WIDTHLABEL);
			this->deck[i]->setFixedHeight(HEIGHTLABEL);
			this->deck[i]->move(QPoint(25 +  j * (25 + WIDTHLABEL), 25 + k * (25 + HEIGHTLABEL)));

			this->deck[i]->setPixmap(img);
		}
	}
}

void Deck_builder::initiate()
{
	int i;
	QString url;
	this->idsPool = readFile();
	this->G = Graph();
	this->G.createCards();
	this->G.createEdges(1, 1, 1, 1, 1);

	vector<int> finalDeck = this->G.heavyNeighbour(this->idsPool);
	vector<int> imgs;
	vector<int>::iterator it;

	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::PreparedStatement *pstmt;

		sql::ResultSet *res;

		driver = get_driver_instance();
		con = driver->connect(HOST, USER, PASS);

		con->setSchema(DB);

		stmt = con->createStatement();

		for (i = 0; i < finalDeck.size(); ++i)
		{
			pstmt = con->prepareStatement("SELECT card.car_id, edition.sca_multiverseid FROM mag_card AS card "
				"LEFT JOIN mag_setcard AS edition ON edition.sca_card = card.car_id WHERE card.car_id IN (?)");

			pstmt->setInt(1, finalDeck[i]);
			pstmt->executeUpdate();

			res = pstmt->executeQuery();

			res->next();
			imgs.push_back(res->getInt("sca_multiverseid"));
		}

		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	//writeFile(imgs);

	QPixmap image;

	for (i = 0; i < DECKSIZE; ++i)
	{
		url = QString::number(imgs[i]);
		url.push_front (R"(C:\Users\guill\Desktop\cards\)");
		url.push_back(".jpg");
		
		image.load(url);
		image = image.scaled(QSize(WIDTHLABEL, HEIGHTLABEL));

		this->deck[i]->setPixmap(image);
	}
}

void Deck_builder::handleOpenButton()
{
	this->idsPool = readFile();

	QMessageBox msgBox;
	msgBox.setWindowTitle("Hello");
	msgBox.setText("You Clicked " + ((QPushButton*)sender())->text());
	msgBox.exec();
}

void Deck_builder::handleSaveButton()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Hello");
	msgBox.setText("You Clicked " + ((QPushButton*)sender())->text());
	msgBox.exec();
}

void Deck_builder::handleAddButton()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Hello");
	msgBox.setText("You Clicked " + ((QPushButton*)sender())->text());
	msgBox.exec();
}