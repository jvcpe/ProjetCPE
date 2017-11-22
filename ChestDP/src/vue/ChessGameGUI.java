package vue;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Observable;
import java.util.Observer;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import model.Coord;
import model.Couleur;
import model.PieceIHM;
import tools.ChessImageProvider;
import controler.ChessGameControlers;


/**
 * @author francoise.perrin -
 * Inspiration Jacques SARAYDARYAN, Adrien GUENARD -
 * Inspiration http://www.roseindia.net/java/example/java/swing/chess-application-swing.shtml
 * 
 *  IHM graphique d'un jeu d'echec 
 *  qui permet à 1 utilisateur de jouer
 *  en prenant successivement le role des blancs puis des noirs.
 *  
 */

public class ChessGameGUI extends JFrame implements MouseListener, MouseMotionListener, Observer{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	// controleur de l'objet métier
	private ChessGameControlers chessGameControler;
	
	//Panneau stratifie permettant de superposer plusieurs couches
	// visibles les unes sur les autres
	private JLayeredPane layeredPane;

	//plateau du jeu d'echec permettant de contenir tous les objets graphiques
	private JPanel chessBoardGuiContainer;

	//piece selectionnee
	private JLabel pieceToMove;

	// carre sur laquelle est posee la piece à deplacer
	private JPanel pieceToMoveSquare;

	// map permettant d'associer un JPanel (carre noir ou blanc)
	// à ses coordonnees sur l'echiquier
	private Map<JPanel, Coord> mapSquareCoord;

	// tableau 2D qui stocke les JPanel
	// permet de rafraichir l'affichage apres chaque deplacement
	// valide par les classes metier
	private JPanel[][] tab2DJPanel;

	// coordonnee qui permettront de recadrer une piece 
	// au milieu du carre lors d'un deplacement  (drag)
	private int xAdjustment;
	private int yAdjustment;

	private Dimension boardSize;



	/**
	 * 
	 * Construit le plateau de l'echiquier sous forme de damier 8*8
	 * et le rend ecoutable par les evenements 
	 * MouseListener et MouseMotionListener.
	 *   
	 * Sont superposes 1 JPanel pour le plateau et
	 * autant de JPanel que de carres noirs ou blancs
	 * sur lesquels seront positionnees les pieces aux bonnes coordonnees.
	 * 
	 * Les images des pieces et leurs coordonnees 
	 * seront fournies par des utilitaires.
	 *
	 * 
	 * @param name - nom de la fenetre

	 * @param chessGameControler - 
	 * @param boardSize - taille de la fenetre
	 */
	public ChessGameGUI(String name, ChessGameControlers chessGameControler, Dimension boardSize) {
		super(name);
		this.chessGameControler = chessGameControler;  
		this.boardSize = boardSize;

		this.mapSquareCoord = new HashMap<JPanel,Coord>();
		this.tab2DJPanel = new JPanel[8][8];

		// construit le plateau de l'echiquier sous forme de damier 8*8  
		this.layeredPane = new JLayeredPane();
		setContentPane(this.layeredPane);	
		this.chessBoardGuiContainer = new JPanel();		
		this.layeredPane.add(this.chessBoardGuiContainer, JLayeredPane.DEFAULT_LAYER);
		this.chessBoardGuiContainer.setLayout( new GridLayout(8, 8) );
		this.chessBoardGuiContainer.setBounds(0, 0, boardSize.width-10, boardSize.height-30);	

		// Ajout des écouteurs pour écouter les évènements souris
		layeredPane.addMouseListener(this);
		layeredPane.addMouseMotionListener(this);

		// le remplissage du damier avec les pièces disposées
		// en fonction de leur place initiale lors de la création de l'échiquier
		// est effectué après appel du constructeur
		// lorsque la vue s'enregistre auprès du ChessGame en tant qu'Observer
		// sa méthode update() est invoquée

	}



	/* (non-Javadoc)
	 * @see java.util.Observer#update(java.util.Observable, java.lang.Object)
	 * 
	 * Cette methode sert à rafraichir l'affichage apres un deplacement effectif
	 * ou une promotion de pion dans la classe metier Echiquier
	 * à partir de la liste de PieceIHM envoyée par l'objet observé (ChessGame)
	 */
	public void update(Observable arg0, Object arg1) {

		List<PieceIHM> piecesIHM = (List<PieceIHM>) arg1;
				
		// rempli le damier abvec des carrés noirs et blancs
		// et les images des pièces aux bonnes coordonnées
		// en fonction des coordonnées retournée par l'objet métier
		this.drawGrid(piecesIHM);
		
		// rafraichi l'affichage après repositionnement de nouveaux composants
		this.revalidate();
	}

	/**
	 * Remplit le plateau de l'echiquier sur lequel  
	 * sont superposes 1 JPanel pour le plateau et
	 * autant de JPanel que de carres noirs ou blancs
	 * + des JLabel pour les images des pièces
	 */
	private void drawGrid(List<PieceIHM> piecesIHM ) {	

		JPanel square = null;
		JLabel pieceGuiLabel = null;

	//	this.layeredPane = new JLayeredPane();
//		setContentPane(this.layeredPane);	
//		this.chessBoardGuiContainer = new JPanel();		
//		this.layeredPane.add(this.chessBoardGuiContainer, JLayeredPane.DEFAULT_LAYER);
//		this.chessBoardGuiContainer.setLayout( new GridLayout(8, 8) );
//		this.chessBoardGuiContainer.setBounds(0, 0, boardSize.width-10, boardSize.height-30);	
		
		// suppression des carrés et images précédentes
		this.chessBoardGuiContainer.removeAll();

		// remplissage du damier avec les carres 
		for (int i = 0; i<8; i++){
			for (int j = 0; j<8; j++) {

				// creation d'un JPanel pour le carre blanc ou noir
				square = this.newSquare(i, j);

				// ajout du carre sur le damier
				this.chessBoardGuiContainer.add( square );

				// sauvegarde des coordonnees logiques du carre
				// sera utile lors des deplacements de pieces					
				this.mapSquareCoord.put(square, new Coord(j, i));
				this.tab2DJPanel[j][i] = square;
			}
		}
		// Ajout des images des pièces sur le damier
		for(PieceIHM pieceIHM : piecesIHM) {			
			for(Coord coord : pieceIHM.getList()) {
				int j = coord.x;
				int i = coord.y;

				// fabrication de l'image de la pièce
				pieceGuiLabel = new JLabel(
						new ImageIcon(ChessImageProvider.getImageFile(
								pieceIHM.getTypePiece(), pieceIHM.getCouleur())));

				// ajout de l'image de piece sur le carre
				square = tab2DJPanel[j][i];
				square.add(pieceGuiLabel);
			}		
		}
	
	}


	/**
	 * @param i
	 * @param j
	 * @return le carre cree sous forme de JPanel
	 */
	private JPanel newSquare(int i, int j){
		JPanel square = new JPanel( new BorderLayout() );
		int row = i % 2;
		if (row == 0) {
			square.setBackground( j % 2 != 0 ? new Color(48, 48, 48) : new Color(242,247, 255)  );
		}
		else {
			square.setBackground( j % 2 != 0 ? new Color(242,247, 255): new Color(48, 48, 48) );
		}
		return square;
	}
	

	/* (non-Javadoc)
	 * @see java.awt.event.MouseListener#mousePressed(java.awt.event.MouseEvent)
	 */
	@Override
	public void mousePressed(MouseEvent e){

		Point pieceToMoveLocation = null;

		Component c =  this.chessBoardGuiContainer.findComponentAt(e.getX(), e.getY());

		this.pieceToMove = null;

		// si l'utilisateur a selectionne une piece
		if (c instanceof JLabel) {
		 
			this.pieceToMove = (JLabel)c;
			this.pieceToMoveSquare=(JPanel)c.getParent();

			pieceToMoveLocation = this.pieceToMoveSquare.getLocation();
			this.xAdjustment = pieceToMoveLocation.x - e.getX();
			this.yAdjustment = pieceToMoveLocation.y - e.getY();

			this.pieceToMove.setLocation(e.getX() + xAdjustment, e.getY() + yAdjustment);
			this.pieceToMove.setSize(pieceToMove.getWidth(), pieceToMove.getHeight());
			this.layeredPane.add(pieceToMove, JLayeredPane.DRAG_LAYER);
		}
	}


	/* (non-Javadoc)
	 * @see java.awt.event.MouseMotionListener#mouseDragged(java.awt.event.MouseEvent)
	 */
	@Override
	public void mouseDragged(MouseEvent e) {
		if (this.pieceToMove != null) {
			this.pieceToMove.setLocation(e.getX() + xAdjustment, e.getY() + yAdjustment);
		}
	}

	/* (non-Javadoc)
	 * @see java.awt.event.MouseListener#mouseReleased(java.awt.event.MouseEvent)
	 */
	@Override
	public void mouseReleased(MouseEvent e) {

		Coord initCoord = null, finalCoord = null ;
		Component targetedComponent = null;
		JPanel targetSquare;

		if(this.pieceToMove != null) {


			this.pieceToMove.setVisible(false);

			// recuperation du composant qui se trouve à position (pixel) finale
			targetedComponent =  this.chessBoardGuiContainer.findComponentAt(e.getX(), e.getY());

			// si c'est un carre occupe, on a recupere une image de piece
			// et il faut recuperer le square qui la contient
			if (targetedComponent instanceof JLabel){
				targetSquare = (JPanel) targetedComponent.getParent();
			}
			// si c'est un carre vide
			else {
				targetSquare = (JPanel)targetedComponent;
			}			

			// recuperation coordonnees initiales et finales de la piece à deplacer
			// en vue du deplacement metier
			initCoord = this.mapSquareCoord.get(this.pieceToMoveSquare);
			finalCoord = this.mapSquareCoord.get(targetSquare);

			// Si les coordonnees finales sont en dehors du damier, on les force à -1
			// cela permettra à la methode chessGame.move de gerer le message d'erreur
			if (finalCoord == null){
				finalCoord = new Coord(-1, -1);
			}

			// Invoque la methode de deplacement de l'echiquier		
			this.chessGameControler.move(initCoord, finalCoord);

			// l'echiquier étant observé par cette vue (fenetre)
			// des lors qu'il est modifie par l'invocation de la méthode move(),
			// la vue en est avertie et
			// sa methode update est appelee pour rafraichir l'affichage du damier

			System.out.println(this.chessGameControler.getMessage());	// A commenter sauf pour verifier si OK

			
		}
	}



	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}



	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}



	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}



	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
}