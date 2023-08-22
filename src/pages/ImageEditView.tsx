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
import { RouteComponentProps } from 'react-router';

import { ImageResultsRepository } from '../utils/ImageRepository';

/* Scanbot SDK Service */
import { ScanbotSDKService } from '../services/ScanbotSDKService';

import { ImageFilter, Page } from 'cordova-plugin-scanbot-sdk';

interface ImageEditViewIdProps extends RouteComponentProps<{ pageId: string; }> { }

const ImageEditView: React.FC<ImageEditViewIdProps> = ({ match }) => {
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
    const filterModal = useRef<HTMLIonModalElement>(null);
    const [present, dismiss] = useIonLoading();
    const [presentAlert] = useIonAlert();
    const [imageData, setImageData] = useState('');
    const [selectedPage, setSelectedPage] = useState(
        ImageResultsRepository.INSTANCE.getPageById(match.params.pageId)!
    );

    useIonViewWillEnter(async () => {
        await loadImageData();
    });

    async function updatePage(page: Page) {
        setSelectedPage(page);
        await ImageResultsRepository.INSTANCE.updatePage(page);
        await loadImageData();
    }

    /* Crop Image */
    async function openCroppingUi() {
        if (!(await ScanbotSDKService.checkLicense())) { return; }

        try {
            const croppingResult = await ScanbotSDKService.SDK.UI.startCroppingScreen({
                page: selectedPage,
                uiConfigs: {
                    doneButtonTitle: 'Save',
                    interfaceOrientation: 'PORTRAIT',
                    topBarBackgroundColor: '#c8193c',
                    bottomBarBackgroundColor: '#c8193c',
                    hintTitle: 'Custom hint:\nDrag the dots to the document edges.',
                    hintTitleColor: '#0000ff'
                }
            });

            if (croppingResult.status === "CANCELED") {
                await presentAlert({
                    header: 'Information',
                    message: 'Cropping screen cancelled.',
                    buttons: ['OK'],
                });
                return;
            }
            await updatePage(croppingResult.page!);
        }
        catch (error) {
            console.log(error);
        }
    }

    /* load image data */
    async function loadImageData() {
        if (!(await ScanbotSDKService.checkLicense())) { return; }

        try {
            const imgData = await ScanbotSDKService.fetchDataFromUri(
                selectedPage.documentPreviewImageFileUri as string
            );
            setImageData(imgData);
        }
        catch (error) {
            console.error(error);
        }
    }

    /* Filter Image */
    async function applyFilter(selectedFilter: ImageFilter) {
        filterModal.current?.dismiss();

        if (!(await ScanbotSDKService.checkLicense())) { return; }

        try {
            filterModal.current?.dismiss();
            await present({
                message: 'Loading...',
                spinner: 'circles'
            });
            const filteredImageResult = await ScanbotSDKService.SDK.applyImageFilterOnPage({
                page: selectedPage,
                imageFilter: selectedFilter
            });
            await dismiss();
            if (filteredImageResult.status === "CANCELED") {
                await presentAlert({
                    header: 'Information',
                    message: 'Image filtering process cancelled.',
                    buttons: ['OK'],
                });
                return;
            }
            await updatePage(filteredImageResult.page);
        }
        catch (error) {
            await dismiss();
            console.error(error);
        }
    }

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar color="primary">
                    <IonButtons slot="start">
                        <IonBackButton />
                    </IonButtons>
                    <IonTitle>Image Edit View</IonTitle>
                </IonToolbar>
            </IonHeader>

            <IonContent fullscreen>
                <IonImg src={imageData} />
            </IonContent>

            <IonFooter>
                <IonToolbar>
                    <IonButtons slot="start">
                        <IonButton onClick={() => openCroppingUi()}>Crop</IonButton>
                    </IonButtons>
                    <IonButtons slot="end">
                        <IonButton id="open-custom-dialog" expand="block">
                            Filter
                        </IonButton>
                        <IonModal id="example-modal" ref={filterModal} trigger="open-custom-dialog">
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