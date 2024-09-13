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
    useIonViewWillEnter,
    IonCard,
} from '@ionic/react';

import './styles/ImageEditView.css';

import { RouteComponentProps } from 'react-router';
import { modalController } from '@ionic/core';

import { ImageResultsRepository } from '../utils/ImageRepository';
import ScanbotService from '../services/scanbot_service';
import { ShowAlert } from '../services/alert_service';
import CommonModalView from './common_components/CommonModalView';
import { FilterOptions } from '../utils/data_util';
import { Page, ParametricFilter } from 'capacitor-plugin-scanbot-sdk';
import { useState } from 'react';

interface ImageEditViewIdProps extends RouteComponentProps<{ pageId: string; }> { }

const ImageEditView: React.FC<ImageEditViewIdProps> = ({ match }) => {

    const [imageData, setImageData] = useState('');
    const [selectedPage, setSelectedPage] = useState(
        ImageResultsRepository.INSTANCE.getPageById(match.params.pageId)!
    );

    useIonViewWillEnter(() => {
        loadImageData();
    });

    async function updatePage(page: Page) {
        setSelectedPage(page);
        await ImageResultsRepository.INSTANCE.updatePage(page);
        await loadImageData();
    }

    /* load image data */
    async function loadImageData() {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const imgData = await ScanbotService.fetchDataFromUri(
                selectedPage.documentPreviewImageFileUri as string
            );
            setImageData(imgData);
        }
        catch (error) {
            console.error(error);
        }
    }

    /* Start the cropping screen */
    const startCroppingScreen = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const croppingResult = await ScanbotService.startCroppingScreen(selectedPage);

            if (croppingResult!.status == 'CANCELED') {
                await ShowAlert('Information', 'Cropping screen has been cancelled.', ['OK']);
                return;
            };
            await updatePage(croppingResult.page!);
        }
        catch (error) {
            await ShowAlert('Start cropping screen Failed', JSON.stringify(error), ['OK']);
        }
    }

    /* Apply filter to the image */
    const onFilterSelected = async (selectedFilterItem: ParametricFilter) => {
        if (!(await ScanbotService.validateLicense())) {
            //filterOptionModal.value.cancel();
            return;
        }

        try {
            const filteredResult = await ScanbotService.applyImageFilterOnPage(
                selectedPage,
                selectedFilterItem
            );
            //filterOptionModal.value.cancel();
            if (filteredResult!.status == 'CANCELED') {
                await ShowAlert('Information', 'Image filtering process has been cancelled.', ['OK']);
                return;
            };

            await updatePage(filteredResult);
            modalController.dismiss();
        }
        catch (error) {
            //filterOptionModal.value.cancel();
            await ShowAlert('Image filtering process Failed', JSON.stringify(error), ['OK']);
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

            <IonContent className='ion-padding'>
                <IonCard>
                    <IonImg src={imageData} />
                </IonCard>
            </IonContent>

            <IonFooter>
                <IonToolbar>
                    <IonButtons slot="start">
                        <IonButton onClick={startCroppingScreen}>Crop</IonButton>
                    </IonButtons>
                    <IonButtons slot="end">
                        <CommonModalView
                            id='filter-modal'
                            modalTitle='Filter Options'
                            buttonTitle='Filter'
                            initialBreakPoint={0.75}
                            optionList={FilterOptions}
                            onItemClick={onFilterSelected} />
                    </IonButtons>
                </IonToolbar>
            </IonFooter>
        </IonPage>
    );
};

export default ImageEditView;