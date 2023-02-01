import { 
    IonContent, 
    IonHeader,
    IonFooter,
    IonPage, 
    IonTitle, 
    IonToolbar, 
    IonButton,
    IonButtons,
    IonBackButton,
    IonImg,
    useIonAlert,
    useIonViewWillEnter } from '@ionic/react';

  import './Home.css';
  
  import React, {useState } from 'react';
  import { RouteComponentProps, useHistory } from 'react-router';
  
  import { ImageResultsRepository } from '../utils/ImageRepository';
  
  import ScanbotSdk, { 
    Page } from 'cordova-plugin-scanbot-sdk';
  
  interface ImageEditViewIdProps extends RouteComponentProps<{
    pageId: string;
}> {}

  const ImageEditView: React.FC<ImageEditViewIdProps> = ({match}) => {
  
    let page = ImageResultsRepository.INSTANCE.getPageById(match.params.pageId);

    const history = useHistory();
    const [presentAlert] = useIonAlert();  
    const [ url, setUrl ] = useState('');
    const [ selectedPage, setSelectedPage ] = useState(page);

    useIonViewWillEnter(() => {
        loadPage();
    });

    // load selected image
    function loadPage() {

        if(page == undefined) return;

        setSelectedPage(page);

        generateImageURL(page); 
    }

    // Scanbot SDK cropping feature
    const imageCrop = (page: Page | undefined) => {

        if (page == undefined){
            return;
        }
        
        ScanbotSdk.UI.startCroppingScreen(
            (croppingResult) => {
 
                if(croppingResult.page == undefined) return;
                ImageResultsRepository.INSTANCE.updatePage(croppingResult.page);

                generateImageURL(croppingResult.page);
            }, 
            (error) => {
                presentAlert({
                    header: 'Error',
                    subHeader: error.status,
                    message: error.message,
                    buttons: ['OK'],
                })
            }, {
            page: page,
            uiConfigs: {
                doneButtonTitle: 'Save',
                interfaceOrientation: 'PORTRAIT',
                topBarBackgroundColor: '#c8193c',
                bottomBarBackgroundColor: '#c8193c',
                hintTitle: 'Custom hint:\nDrag the dots to the document edges.',
                hintTitleColor: '#0000ff'
            }})
    }

    // scanbot SDK generate image url feature
    const generateImageURL = (page: Page) => {
        ScanbotSdk.getImageData((result) => {

            const extension = 'png';

            let url = `data:image/${extension};base64,` + result.base64ImageData;

            setUrl(url);
        },
        (error) => {
            presentAlert({
                header: 'Error',
                subHeader: error.status,
                message: error.message,
                buttons: ['OK'],
            })
         },
        { imageFileUri: page.documentPreviewImageFileUri as string }); 
    }

    return (
      <IonPage>
        <IonHeader>
          <IonToolbar>
            <IonButtons slot="start">
                <IonBackButton />
            </IonButtons>
            <IonTitle>Image Edit View</IonTitle>
          </IonToolbar>
        </IonHeader>

        <IonContent fullscreen>
            <IonImg src={url} />
        </IonContent>

        <IonFooter>
            <IonToolbar>
                <IonButtons slot="start">
                    <IonButton onClick = { async () => {
                        imageCrop(selectedPage);
                    }}>Crop</IonButton>
                </IonButtons>
                <IonButtons slot="end">
                    <IonButton>Filtter</IonButton>
                </IonButtons>
            </IonToolbar>
      </IonFooter>
      </IonPage>
    );
  };
  
  export default ImageEditView;