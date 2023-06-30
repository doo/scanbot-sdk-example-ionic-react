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
        if (page === undefined) {
            alert('Can not find a valid document. Please try again!');
            return;
        }
        setSelectedPage(page);
        await generateImageURL(page);
    }

    /* Crop Image */
    const imageCrop = async (page: Page | undefined) => {
        if(!(await ScanbotSDKService.checkLicense())) {
            alert('Scanbot SDK (trial) license has expired!');
            return;
        }
        if (page === undefined) {
            alert('Can not find valid page. Please try again!');
            return;
        }

        try {
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

            if (croppingResult.status === "CANCELED") {
                await presentAlert({
                    header: 'Error',
                    message: 'Cropping screen cancelled. Please try again!',
                    buttons: ['OK'],
                })
                return;
            }
            await ImageResultsRepository.INSTANCE.updatePage(croppingResult.page!);
            await generateImageURL(croppingResult.page!);
        }
        catch (error) {
            console.log(error);
        }
    }

    /* Generate image url */
    const generateImageURL = async (page: Page) => {
        if(!(await ScanbotSDKService.checkLicense())) {
            alert('Scanbot SDK (trial) license has expired!');
            return;
        }
        if (page === undefined) {
            alert('Can not find valid page. Please try again!');
            return;
        }

        try {
            setSelectedPage(page);
            const imageURL = await ScanbotSDKService.fetchDataFromUri(page.documentPreviewImageFileUri as string);

            if(imageURL === '' || imageURL === undefined) {
                alert('Can not find valid image path. Please try again!');
                return;
            }
            setUrl(imageURL);
        }
        catch (error) {
            console.error(error);
        }
    }

    /* Filter Image */
    const applyFilter = async (selectedFilterOption: string) => {
        if(!(await ScanbotSDKService.checkLicense())) {
            modal.current?.dismiss();
            alert('Scanbot SDK (trial) license has expired!');
            return;
        }
        if (page === undefined) {
            modal.current?.dismiss();
            alert('Can not find valid page. Please try again!');
            return;
        }

        try {
            modal.current?.dismiss();
            await present({
                message: 'Loading...',
                spinner: 'circles'
            })
            const filteredImageResult = await ScanbotSDKService.SDK.applyImageFilterOnPage({
                page: page,
                imageFilter: selectedFilterOption as ImageFilter
            });
            await dismiss();
            if (filteredImageResult.status === "CANCELED") {
                await presentAlert({
                    header: 'Error',
                    message: 'Image filtering process cancelled. Please try again!',
                    buttons: ['OK'],
                })
                return;
            }
            await ImageResultsRepository.INSTANCE.updatePage(filteredImageResult.page);
            await generateImageURL(filteredImageResult.page);
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
                <IonImg src={url} />
            </IonContent>

            <IonFooter>
                <IonToolbar>
                    <IonButtons slot="start">
                        <IonButton onClick={async () => { await imageCrop(selectedPage); }}>Crop</IonButton>
                    </IonButtons>
                    <IonButtons slot="end">
                        <IonButton id="open-custom-dialog" expand="block">
                            Filter
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