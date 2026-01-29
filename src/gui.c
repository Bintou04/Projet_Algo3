#include "gui.h"
#include "support.h"
#include "database.h"
#include <string.h>
#include <stdlib.h>

/* Variables globales */
static Element **listeGlobale;
static GtkWidget *zoneAffichage;
static GtkWidget *entryId;
static GtkWidget *entryTitre;
static GtkWidget *entryModule;
static GtkWidget *entryType;
static GtkWidget *entryEnseignant;
static GtkWidget *entryAuteur;

/* ==================== AFFICHER TOUS LES SUPPORTS ==================== */
void on_afficher_clicked(GtkWidget *widget, gpointer data) {
    Element *temp = *listeGlobale;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage));
    
    if (temp == NULL) {
        gtk_text_buffer_set_text(buffer, "📭 Aucun support disponible", -1);
        return;
    }
    
    char texte[10000] = "";
    strcat(texte, "📚 LISTE DES SUPPORTS PÉDAGOGIQUES\n");
    strcat(texte, "═══════════════════════════════════════════════════════════════\n\n");
    
    while (temp != NULL) {
        char ligne[500];
        snprintf(ligne, sizeof(ligne), 
            "🆔 ID: %d\n"
            "📖 Titre: %s\n"
            "📘 Module: %s\n"
            "📄 Type: %s\n"
            "👨‍🏫 Enseignant: %s\n"
            "📂 Chemin: %s\n"
            "───────────────────────────────────────────────────────────────\n\n",
            temp->support.id,
            temp->support.titre,
            temp->support.module,
            temp->support.type,
            temp->support.enseignant,
            temp->support.chemin
        );
        strcat(texte, ligne);
        temp = temp->suivant;
    }
    
    gtk_text_buffer_set_text(buffer, texte, -1);
}

/* ==================== AJOUTER UN SUPPORT ==================== */
void on_ajouter_clicked(GtkWidget *widget, gpointer data) {
    Support s;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage));
    
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entryId));
    const char *titre_text = gtk_entry_get_text(GTK_ENTRY(entryTitre));
    const char *module_text = gtk_entry_get_text(GTK_ENTRY(entryModule));
    const char *type_text = gtk_entry_get_text(GTK_ENTRY(entryType));
    const char *enseignant_text = gtk_entry_get_text(GTK_ENTRY(entryEnseignant));
    const char *auteur_text = gtk_entry_get_text(GTK_ENTRY(entryAuteur));

    // Validation
    if (strlen(id_text) == 0 || strlen(titre_text) == 0 || strlen(module_text) == 0) {
        gtk_text_buffer_set_text(buffer, "❌ ERREUR: ID, Titre et Module sont obligatoires !", -1);
        return;
    }

    s.id = atoi(id_text);
    strncpy(s.titre, titre_text, sizeof(s.titre) - 1);
    strncpy(s.module, module_text, sizeof(s.module) - 1);
    strncpy(s.type, strlen(type_text) > 0 ? type_text : "Non spécifié", sizeof(s.type) - 1);
    strncpy(s.enseignant, strlen(enseignant_text) > 0 ? enseignant_text : "Non spécifié", sizeof(s.enseignant) - 1);
    strncpy(s.chemin, strlen(auteur_text) > 0 ? auteur_text : "", sizeof(s.chemin) - 1);

    // Ajouter à la liste
    *listeGlobale = ajouterSupport(*listeGlobale, s);
    
    // Sauvegarder dans la base
    insertSupportToDB(s);
    
    gtk_text_buffer_set_text(buffer, "✅ Support ajouté avec succès !", -1);
    
    // Vider les champs
    gtk_entry_set_text(GTK_ENTRY(entryId), "");
    gtk_entry_set_text(GTK_ENTRY(entryTitre), "");
    gtk_entry_set_text(GTK_ENTRY(entryModule), "");
    gtk_entry_set_text(GTK_ENTRY(entryType), "");
    gtk_entry_set_text(GTK_ENTRY(entryEnseignant), "");
    gtk_entry_set_text(GTK_ENTRY(entryAuteur), "");
}

/* ==================== SUPPRIMER UN SUPPORT ==================== */
void on_supprimer_clicked(GtkWidget *widget, gpointer data) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage));
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entryId));
    
    if (strlen(id_text) == 0) {
        gtk_text_buffer_set_text(buffer, "❌ ERREUR: Veuillez entrer un ID", -1);
        return;
    }
    
    int id = atoi(id_text);
    
    // Supprimer de la liste
    *listeGlobale = supprimerSupport(*listeGlobale, id);
    
    // Supprimer de la base
    deleteSupportFromDB(id);
    
    gtk_text_buffer_set_text(buffer, "🗑️ Support supprimé avec succès", -1);
    gtk_entry_set_text(GTK_ENTRY(entryId), "");
}

/* ==================== RECHERCHER UN SUPPORT ==================== */
void on_rechercher_clicked(GtkWidget *widget, gpointer data) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage));
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entryId));
    
    if (strlen(id_text) == 0) {
        gtk_text_buffer_set_text(buffer, "❌ ERREUR: Veuillez entrer un ID", -1);
        return;
    }
    
    int id = atoi(id_text);
    Element *resultat = rechercherSupport(*listeGlobale, id);
    
    if (resultat != NULL) {
        char texte[1000];
        snprintf(texte, sizeof(texte),
            "🔍 SUPPORT TROUVÉ\n"
            "═══════════════════════════════════════════════════════════════\n\n"
            "🆔 ID: %d\n"
            "📖 Titre: %s\n"
            "📘 Module: %s\n"
            "📄 Type: %s\n"
            "👨‍🏫 Enseignant: %s\n"
            "📂 Chemin: %s\n",
            resultat->support.id,
            resultat->support.titre,
            resultat->support.module,
            resultat->support.type,
            resultat->support.enseignant,
            resultat->support.chemin
        );
        gtk_text_buffer_set_text(buffer, texte, -1);
    } else {
        gtk_text_buffer_set_text(buffer, "❌ Support introuvable", -1);
    }
}

/* ==================== LANCER L'INTERFACE GTK ==================== */
void lancerGUI(int argc, char *argv[], Element **liste) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *grid;
    GtkWidget *btnAfficher, *btnAjouter, *btnSupprimer, *btnRechercher;
    GtkWidget *scrolled;
    GtkCssProvider *cssProvider;
    
    listeGlobale = liste;

    gtk_init(&argc, &argv);
    
    // Connexion base de données et chargement
    if (connectDatabase() != 0) {
        g_print("ERREUR: Impossible de se connecter à la base de données\n");
    }
    loadSupportsFromDB();
    
    // IMPORTANT: Synchroniser tete avec listeGlobale
    extern Element *tete;
    *liste = tete;

    /* Fenêtre principale */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "🎓 Gestion de Supports Pédagogiques");
    gtk_window_set_default_size(GTK_WINDOW(window), 850, 750);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    /* Container principal */
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    /* Titre */
    GtkWidget *titre = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(titre), "<span size='large' weight='bold' foreground='#2E5C8A'>📚 Gestion de Supports Pédagogiques</span>");
    gtk_box_pack_start(GTK_BOX(vbox), titre, FALSE, FALSE, 5);

    /* Grille pour les champs */
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 8);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 8);
    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);

    /* Champs de saisie */
    GtkWidget *lblId = gtk_label_new("🆔 ID:");
    GtkWidget *lblTitre = gtk_label_new("📖 Titre:");
    GtkWidget *lblModule = gtk_label_new("📘 Module:");
    GtkWidget *lblType = gtk_label_new("📄 Type:");
    GtkWidget *lblEnseignant = gtk_label_new("👨‍🏫 Enseignant:");
    GtkWidget *lblAuteur = gtk_label_new("📂 Chemin:");

    entryId = gtk_entry_new();
    entryTitre = gtk_entry_new();
    entryModule = gtk_entry_new();
    entryType = gtk_entry_new();
    entryEnseignant = gtk_entry_new();
    entryAuteur = gtk_entry_new();

    gtk_entry_set_placeholder_text(GTK_ENTRY(entryId), "Ex: 1");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryTitre), "Ex: Introduction à Python");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryModule), "Ex: Algorithmique");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryType), "Ex: Cours, TD, TP");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryEnseignant), "Ex: Dr. Diop");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryAuteur), "Ex: /documents/cours.pdf");

    gtk_grid_attach(GTK_GRID(grid), lblId, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entryId, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), lblTitre, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entryTitre, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), lblModule, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entryModule, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), lblType, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entryType, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), lblEnseignant, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entryEnseignant, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), lblAuteur, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entryAuteur, 1, 5, 1, 1);

    gtk_widget_set_hexpand(entryId, TRUE);
    gtk_widget_set_hexpand(entryTitre, TRUE);
    gtk_widget_set_hexpand(entryModule, TRUE);
    gtk_widget_set_hexpand(entryType, TRUE);
    gtk_widget_set_hexpand(entryEnseignant, TRUE);
    gtk_widget_set_hexpand(entryAuteur, TRUE);

    /* Boutons d'action */
    GtkWidget *btnBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    gtk_box_pack_start(GTK_BOX(vbox), btnBox, FALSE, FALSE, 5);

    btnAjouter = gtk_button_new_with_label("➕ Ajouter");
    btnSupprimer = gtk_button_new_with_label("🗑️ Supprimer");
    btnRechercher = gtk_button_new_with_label("🔍 Rechercher");
    btnAfficher = gtk_button_new_with_label("📋 Afficher Tout");

    gtk_box_pack_start(GTK_BOX(btnBox), btnAjouter, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(btnBox), btnSupprimer, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(btnBox), btnRechercher, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(btnBox), btnAfficher, TRUE, TRUE, 0);

    /* Zone d'affichage scrollable */
    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), 
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolled, -1, 350);
    
    zoneAffichage = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(zoneAffichage), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(zoneAffichage), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(scrolled), zoneAffichage);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 0);

    /* CSS pour le style */
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider,
        "window { background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); }"
        "button { "
        "  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);"
        "  color: white;"
        "  border-radius: 6px;"
        "  padding: 8px 16px;"
        "  font-weight: bold;"
        "  border: none;"
        "  min-height: 35px;"
        "}"
        "button:hover { opacity: 0.9; }"
        "entry { "
        "  border-radius: 5px;"
        "  padding: 8px;"
        "  border: 2px solid #e0e0e0;"
        "  min-height: 30px;"
        "}"
        "textview { "
        "  background-color: white;"
        "  border-radius: 8px;"
        "  padding: 12px;"
        "  font-family: monospace;"
        "  font-size: 12px;"
        "}"
        "label { "
        "  color: white;"
        "  font-weight: bold;"
        "  font-size: 13px;"
        "}",
        -1, NULL);
    
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(cssProvider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    /* Connexion des signaux */
    g_signal_connect(btnAjouter, "clicked", G_CALLBACK(on_ajouter_clicked), NULL);
    g_signal_connect(btnSupprimer, "clicked", G_CALLBACK(on_supprimer_clicked), NULL);
    g_signal_connect(btnRechercher, "clicked", G_CALLBACK(on_rechercher_clicked), NULL);
    g_signal_connect(btnAfficher, "clicked", G_CALLBACK(on_afficher_clicked), NULL);

    /* Message de bienvenue */
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage));
    gtk_text_buffer_set_text(buffer, 
        "👋 Bienvenue dans le système de gestion de supports pédagogiques !\n\n"
        "📌 Utilisez les boutons ci-dessus pour gérer vos supports.\n"
        "📌 Cliquez sur 'Afficher Tout' pour voir tous les supports.", -1);

    gtk_widget_show_all(window);
    gtk_main();
    
    closeDatabase();
}