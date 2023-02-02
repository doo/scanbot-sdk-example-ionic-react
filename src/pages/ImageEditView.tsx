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
    IonModal,
    IonList,
    IonItem,
    IonLabel,
    useIonLoading,
    useIonViewWillEnter
} from '@ionic/react';

import './styles/ImageEditView.css';

import React, { useState, useRef } from 'react';
import { RouteComponentProps, useHistory } from 'react-router';

import { ImageResultsRepository } from '../utils/ImageRepository';

/* Scanbot SDK Service */
import { ScanbotSDKService } from '../services/ScanbotSDKService';

import { ImageFilter, Page } from 'cordova-plugin-scanbot-sdk';

interface ImageEditViewIdProps extends RouteComponentProps<{ pageId: string; }> { }

const ImageEditView: React.FC<ImageEditViewIdProps> = ({ match }) => {

    let page: any = undefined;
    page = ImageResultsRepository.INSTANCE.getPageById(match.params.pageId);

    const imageFilterList: ImageFilter[] = [
        'NONE',
        'COLOR_ENHANCED',
        'GRAYSCALE',
        'BINARIZED',
        'COLOR_DOCUMENT',
        'PURE_BINARIZED',
        'BACKGROUND_CLEAN',
        'BLACK_AND_WHITE',
        'OTSU_BINARIZATION',
        'DEEP_BINARIZATION',
        'EDGE_HIGHLIGHT',
        'LOW_LIGHT_BINARIZATION',
        'LOW_LIGHT_BINARIZATION_2',
        'SENSITIVE_BINARIZATION'
    ];

    const history = useHistory();
    const modal = useRef<HTMLIonModalElement>(null);
    const [present, dismiss] = useIonLoading();
    const [presentAlert] = useIonAlert();
    const [url, setUrl] = useState('');
    const [selectedPage, setSelectedPage] = useState(page);

    useIonViewWillEnter(async () => {
        await loadPage();
    });

    // load selected image
    async function loadPage() {

        if (page == undefined) return;

        setSelectedPage(page);

        await generateImageURL(page);
    }

    // Scanbot SDK cropping feature
    const imageCrop = async (page: Page | undefined) => {

        if (page == undefined) {
            return;
        }

        const croppingResult = await ScanbotSDKService.SDK.UI.startCroppingScreen({
            page: page,
            uiConfigs: {
                doneButtonTitle: 'Save',
                interfaceOrientation: 'PORTRAIT',
                topBarBackgroundColor: '#c8193c',
                bottomBarBackgroundColor: '#c8193c',
                hintTitle: 'Custom hint:\nDrag the dots to the document edges.',
                hintTitleColor: '#0000ff'
            }
        });

        try {
            if (croppingResult.page == undefined) return;

            ImageResultsRepository.INSTANCE.updatePage(croppingResult.page);

            generateImageURL(croppingResult.page);

        } catch (error) {
            console.log(error);
        }
    }

    // scanbot SDK generate image url feature
    const generateImageURL = async (page: Page) => {

        try {
            setSelectedPage(page);

            const imageURL = await ScanbotSDKService.fetchDataFromUri(page.documentPreviewImageFileUri as string);

            setUrl(imageURL);

        } catch (error) {
            console.error(error);
        }
    }

    // scanbot image filter feature
    const applyFilter = async (selectedFilterOption: string) => {

        modal.current?.dismiss();

        if (page == undefined) return;

        try {
            present({
                message: 'Loading...',
                spinner: 'circles'
            })
    
            const filteredImageResult = await ScanbotSDKService.SDK.applyImageFilterOnPage({
                page: page,
                imageFilter: selectedFilterOption as ImageFilter
            });
    
            if (filteredImageResult.status == "CANCELED") return
    
            ImageResultsRepository.INSTANCE.updatePage(filteredImageResult.page);
            generateImageURL(filteredImageResult.page);
    
            dismiss();

        } catch (error) {
            console.error(error);
        }
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
                        <IonButton onClick={async () => { imageCrop(selectedPage); }}>Crop</IonButton>
                    </IonButtons>
                    <IonButtons slot="end">
                        <IonButton id="open-custom-dialog" expand="block">
                            Filtter
                        </IonButton>

                        <IonModal id="example-modal" ref={modal} trigger="open-custom-dialog">
                            <div className="wrapper">
                                <h1>Filter Formats</h1>

                                <IonList lines="inset">
                                    {imageFilterList.map((item) => (
                                        <IonItem button={true} detail={false} onClick={() => applyFilter(item)}>
                                            <IonLabel>{item}</IonLabel>
                                        </IonItem>
                                    ))}

                                </IonList>
                            </div>
                        </IonModal>
                    </IonButtons>
                </IonToolbar>
            </IonFooter>
        </IonPage>
    );
};

export default ImageEditView;