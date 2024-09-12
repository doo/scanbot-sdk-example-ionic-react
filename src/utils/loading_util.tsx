import { IonLoading } from '@ionic/react';

function Example() {
    return (
        <>
            <IonLoading isOpen={true} trigger="open-loading" message="Loading" />
        </>
    );
}
export default Example;